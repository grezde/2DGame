#include "Game.h"
#include "Globals.h"
#include <iostream>

Game* Game::curentGame = nullptr;

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Johnson Simultator v0.1.2");
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
                for(Scene* sc : weakscenes)
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
            for (int j = scenes.size()-1; j >= 0; j--)
                scenes[j]->update(dt);
        }
        else
            scenes.back()->update(dt);
        for (Scene* sc : weakscenes)
            sc->update(dt);
        
        Scene* nextScene = scenes.back()->nextScene();
        if (nextScene == nullptr)
            nextScene = next;
        if (clearAll) {
            while (!scenes.empty()) {
                delete scenes.back();
                scenes.pop_back();
            }
            while (!weakscenes.empty()) {
                delete weakscenes.back();
                weakscenes.pop_back();
            }
            clearAll = false;
        }
        else {
            if (scenes.back()->shouldQuit() || exit) {
                delete scenes.back();
                scenes.pop_back();
                if (!scenes.empty())
                    scenes.back()->reinit();
                exit = false;
            }
            for (int i = 0; i < weakscenes.size(); i++)
                if (weakscenes[i]->shouldQuit()) {
                    delete weakscenes[i];
                    weakscenes.erase(weakscenes.begin() + i);
                    i = 0;
                }
        }
        if (nextScene != nullptr) {
            if (nextScene->updateBeneath())
                weakscenes.push_back(nextScene);
            else {
                if (!scenes.empty())
                    scenes.back()->nextScene(nullptr);
                scenes.push_back(nextScene);
            }
            nextScene->onWindowResize(sf::Vector2i(window->getSize().x, window->getSize().y));
            nextScene->init();
            next = nullptr;
        }
        if (scenes.size() == 0) {
            window->close();
            return;
        }

        window->clear();
        for (Scene* scene : scenes)
            window->draw(*scene, scene->getTransform());
        for(Scene* scene : weakscenes)
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
