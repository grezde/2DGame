#include "MenuScene.h"
#include "Game.h"
#include <iostream>

MenuScene::MenuScene()
	: ButtonSetScene({ "Continue", "New Game", "Quit" }, sf::FloatRect(200, 100, 400, 400))
{
	backTex.loadFromFile("Files/global/mech_board.png");
	backSpr.setTexture(backTex);
	backSpr.setScale(float(Game::WIDTH) / float(backTex.getSize().x), float(Game::HEIGHT) / float(backTex.getSize().y));
}

MenuScene::~MenuScene()
{

}

void MenuScene::draw(sf::RenderWindow* window)
{
	window->draw(backSpr);
	ButtonSet::draw(window);
}

void MenuScene::update(float dt)
{
	ButtonSet::update(dt);
}

void MenuScene::finsihedSelection(int selected)
{
	std::cout << "YES!";
}
