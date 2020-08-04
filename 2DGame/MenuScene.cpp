#include "MenuScene.h"
#include "Game.h"
#include <iostream>
#include "WalkingScene.h"
#include "SaveSelectionScene.h"
#include "Save.h"
#include "SpeechCutScenes.h"

void MenuScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backSpr, states);
	target.draw(bs, states);
}

MenuScene::MenuScene()
	: bs(this)
{
	backTex.loadFromFile("Files/global/mech_board.png");
	backSpr.setTexture(backTex);
	backSpr.setScale(float(Game::WIDTH) / float(backTex.getSize().x), float(Game::HEIGHT) / float(backTex.getSize().y));
}

MenuScene::~MenuScene()
{

}

void MenuScene::update(float dt)
{
	bs.update(dt);
}

MainMenuButtonSet::MainMenuButtonSet(MenuScene* parent)
	: parent(parent), ButtonSet({ "Continue", "New Game", "Quit" }, sf::FloatRect(350, 200, 350, 300))
{
	if (Save::getSaves().size() == 0) {
		buttons[0].setEnabled(false);
		select(1);
	}
}

void MainMenuButtonSet::finsihedSelection(int selected)
{
	parent->exit = true;
	if (selected == 2)
		return;
	if (selected == 1)
		parent->next = new WelcomeSCS();
	if (selected == 0)
		parent->next = new SaveSelectionScene();
}
