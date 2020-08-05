#include "Game.h"
#include "Globals.h"
#include <iostream>

Game* Game::curentGame = nullptr;

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Johnson INC");
    Globals::font = new sf::Font();
    Globals::font->loadFromFile("Files/other/FFFForward.TTF");
}

void Game::run(Scene* initialScene)
{
    curentGame = this;

    scenes.push_back(initialScene);
    initialScene->init();

    float t = 0, n=0;

    sf::Clock clock;
    sf::Time previous = clock.getElapsedTime();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed)
                scenes.back()->onKeyPress(event.key.code);
            if (event.type == sf::Event::TextEntered)
                scenes.back()->onTextEntered(event.text.unicode);
            if (event.type == sf::Event::MouseButtonPressed)
                scenes.back()->onMousePress(event.mouseButton.button, { event.mouseButton.x, event.mouseButton.y });
            if (event.type == sf::Event::Resized) {
                for(Scene* sc : scenes)
                    sc->onWindowResize(sf::Vector2i(event.size.width, event.size.height));
            }
        }
        
        sf::Time current = clock.getElapsedTime();
        float dt = float((current - previous).asMicroseconds()) / 1e6;
        previous = current;
        if (dt > 0.05f)
            dt = 0;
        if (updateAll) {
            updateAll = false;
            for (int i = scenes.size() - 1; i >= 0; i--)
                scenes[i]->update(dt);
        }
        else if(!scenes.empty()) {
            int i = scenes.size()-1;
            scenes[i]->update(dt);
            while (scenes[i]->updateBeneath() && i > 0) {
                i--;
                scenes[i]->update(dt);
            }
        }

        Scene* nextScene = scenes.back()->nextScene();
        if (nextScene == nullptr)
            nextScene = next;
        if (clearAll) {
            while (!scenes.empty()) {
                delete scenes.back();
                scenes.pop_back();
            }
            clearAll = false;
        }
        else if (scenes.back()->shouldQuit() || exit) {
            delete scenes.back();
            scenes.pop_back();
            if (!scenes.empty()) {
                scenes.back()->reinit();
                scenes.back()->onWindowResize(sf::Vector2i(window->getSize().x, window->getSize().y));
            }
            exit = false;
        }
        if (nextScene != nullptr) {
            if (!scenes.empty())
                scenes.back()->nextScene(nullptr);
            scenes.push_back(nextScene);
            nextScene->onWindowResize(sf::Vector2i(window->getSize().x, window->getSize().y));
            nextScene->init();
            next = nullptr;
        }
        if (scenes.size() == 0) {
            window->close();
            return;
        }

        window->clear();
        for (auto scene : scenes)
            window->draw(*scene, scene->getTransform());
        window->display();
    }
}

void Game::setNextScene(bool shouldExit, Scene* nextScene)
{
    exit = shouldExit;
    next = nextScene;
}

Game::~Game()
{
    delete window;
}
