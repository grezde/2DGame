#include "CircleScene.h"
#include "SquareScene.h"
#include "Game.h"

void CircleScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::A) {
		next = new SquareScene();
		exit = true;
	}
}

void CircleScene::init()
{
	shape.setRadius(100.0f);
	shape.setOrigin(100, 100);
	shape.setPosition(Game::WIDTH / 2, Game::HEIGHT / 2);
	shape.setFillColor(sf::Color::Green);
}

void CircleScene::draw(sf::RenderWindow* window)
{
	window->draw(shape);
}

void CircleScene::update(float dt)
{
}
