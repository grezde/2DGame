#include "Game.h"

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
}

void Game::run(Scene* initialScene)
{
    scenes.push_back(initialScene);
    initialScene->init();

    sf::Clock clock;
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
        
        sf::Time dt = clock.getElapsedTime();
        scenes.back()->update(float(dt.asMicroseconds()) / 1e6);
        
        Scene* next = scenes.back()->nextScene();
        if (scenes.back()->shouldQuit()) {
            delete scenes.back();
            scenes.pop_back();
        }
        if (next != nullptr) {
            scenes.push_back(next);
            next->init();
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

Game::~Game()
{
    delete window;
}
