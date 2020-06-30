#include "Game.h"

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
}

void Game::run(Scene* initialScene)
{
    scenes.push_back(initialScene);
    initialScene->init();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        
        if (scenes.size() == 0)
            return;
        scenes.back()->update(0.1f);

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
