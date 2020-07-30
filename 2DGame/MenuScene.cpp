#include "MenuScene.h"
#include "Game.h"

MenuScene::MenuScene()
{
	backTex.loadFromFile("Files/global/mech_board.png");
	backSpr.setTexture(backTex);
	backSpr.setScale(float(Game::WIDTH) / float(backTex.getSize().x), float(Game::HEIGHT) / float(backTex.getSize().y));
	buttons.push_back(Button("Continue", sf::FloatRect(100, 100, 300, 100)));
}

MenuScene::~MenuScene()
{

}

void MenuScene::draw(sf::RenderWindow* window)
{
	window->draw(backSpr);
	for (Button& b : buttons)
		b.draw(window);
}

void MenuScene::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		buttons.back().setSelected(true);
	else
		buttons.back().setSelected(false);
}
