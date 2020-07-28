#include "Game.h"
#include "Globals.h"

Game* Game::curentGame = nullptr;

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Johnson INC");
    Globals::save = new Save("test");
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
        }
        
        sf::Time current = clock.getElapsedTime();
        scenes.back()->update(float((current-previous).asMicroseconds()) / 1e6);
        previous = current;

        Scene* nextScene = scenes.back()->nextScene();
        if (scenes.back()->shouldQuit() || exit) {
            delete scenes.back();
            scenes.pop_back();
            exit = false;
        }
        if (nextScene != nullptr) {
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
        for (auto scene : scenes)
            scene->draw(window);
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
