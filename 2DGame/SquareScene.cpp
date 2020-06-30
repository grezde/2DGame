#include "SquareScene.h"
#include "CircleScene.h"
#include "Game.h"

void SquareScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::D) {
		next = new CircleScene();
		exit = true;
	}
}

void SquareScene::init()
{
	rect.setSize(sf::Vector2f(300, 300));
	rect.setOrigin(150, 150);
	rect.setPosition(Game::WIDTH / 2, Game::HEIGHT / 2);
	rect.setFillColor(sf::Color::Red);
}

void SquareScene::draw(sf::RenderWindow* window)
{
	window->draw(rect);
}

void SquareScene::update(float dt)
{

}
