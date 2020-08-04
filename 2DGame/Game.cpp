#include "Game.h"
#include "Globals.h"

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
            if (event.type == sf::Event::MouseButtonPressed) {
                scenes.back()->onMousePress(event.mouseButton);
            }
        }
        
        sf::Time current = clock.getElapsedTime();
        float dt = float((current - previous).asMicroseconds()) / 1e6;
        previous = current;
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
        if (scenes.back()->shouldQuit() || exit) {
            delete scenes.back();
            scenes.pop_back();
            if(!scenes.empty())
                scenes.back()->reinit();
            exit = false;
        }
        if (nextScene != nullptr) {
            if (!scenes.empty())
                scenes.back()->nextScene(nullptr);
            scenes.push_back(nextScene);
            nextScene->init();
        }
        if (next != nullptr) {
            scenes.push_back(next);
            next->init();
            next = nullptr;
        }
        if (scenes.size() == 0) {
            window->close();
            return;
        }

        window->clear();
        for (auto scene : scenes) {
            scene->draw(window);
            window->draw(*scene);
        }
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
