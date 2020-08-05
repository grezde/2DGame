#include "PauseMenuScene.h"
#include "MenuScene.h"
#include "Globals.h"
#include "Game.h"

PauseMenuScene::PauseMenuScene()
	: bs(this)
{
	backtex.loadFromFile("Files/global/small_board.png");
}

void PauseMenuScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bs, states);
}

void PauseMenuScene::update(float dt)
{
}

void PauseMenuScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
		exit = true;
	else
		bs.onKeyPress(key);
}

PauseMenuBS::PauseMenuBS(PauseMenuScene* parent)
	: parent(parent), ButtonSet({ "Resume", "Save", "Main Menu" }, sf::FloatRect(300, 200, 200, 200))
{
}

void PauseMenuBS::finsihedSelection(int selected)
{
	parent->exit = true;
	if (selected == 0)
		parent->next = nullptr;
	else if (selected == 1)
		Globals::save->loadToFile();
	else {
		parent->next = new MenuScene();
		Game::curent()->clearAllScenes();
	}
}
