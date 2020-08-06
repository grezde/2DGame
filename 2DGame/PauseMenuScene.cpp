#include "PauseMenuScene.h"
#include "MenuScene.h"
#include "Globals.h"
#include "Game.h"
#include "SavePopupScene.h"

PauseMenuScene::PauseMenuScene()
	: bs(this), cbs(this)
{
	backtex.loadFromFile("Files/global/small_board.png");
	backspr.setTexture(backtex);
	backspr.setOrigin(backtex.getSize().x / 2, backtex.getSize().y / 2);
	backspr.setPosition(Game::WIDTH / 2, Game::HEIGHT / 2);
	confirmText.setFont(*Globals::font);
	confirmText.setCharacterSize(20);
	confirmText.setPosition(290, 200);
	confirmText.setString("      Ai munca\n      nesalvata.\n Ce vrei sa faci?");
	confirmText.setFillColor(sf::Color::White);
}

void PauseMenuScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backspr, states);
	if (confirmation) {
		target.draw(confirmText, states);
		target.draw(cbs, states);
	}
	else
		target.draw(bs, states);
}

void PauseMenuScene::update(float dt)
{
}

void PauseMenuScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
		exit = true;
	else if (confirmation)
		cbs.onKeyPress(key);
	else
		bs.onKeyPress(key);
}

PauseMenuBS::PauseMenuBS(PauseMenuScene* parent)
	: parent(parent), ButtonSet({ "Resume", "Save", "Main Menu" }, sf::FloatRect(300, 200, 200, 200))
{
}

void PauseMenuBS::finsihedSelection(int selected)
{
	if (selected == 0) {
		parent->exit = true;
		parent->next = nullptr;
	}
	else if (selected == 1) {
		Globals::save->loadToFile(true);
		Game::curent()->setNextScene(false, new SavePopupScene(Globals::save->saveName()));
	}
	else {
		if (!Globals::save->wasModified()) {
			parent->next = new MenuScene();
			Game::curent()->clearAllScenes();
		}
		else
			parent->confirmation = true;
	}
}

PauseMenuConfirmationBS::PauseMenuConfirmationBS(PauseMenuScene* parent)
	: parent(parent), ButtonSet({ "Save and leave", "Don't save" }, sf::FloatRect(300, 300, 200, 100), 0.2f)
{
}

void PauseMenuConfirmationBS::finsihedSelection(int selected)
{
	if (selected == 0)
		Globals::save->loadToFile(true);
	parent->next = new MenuScene();
	Game::curent()->clearAllScenes();
}
