#include "SaveSelectionScene.h"
#include "Save.h"
#include "Game.h"
#include "Globals.h"
#include "WalkingScene.h"
#include "MenuScene.h"

void SaveSelectionScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backSpr, states);
	target.draw(bs, states);
}

SaveSelectionScene::SaveSelectionScene()
	: bs(this)
{
	backTex.loadFromFile("Files/global/mech_board.png");
	backSpr.setTexture(backTex);
	backSpr.setScale(float(Game::WIDTH) / float(backTex.getSize().x), float(Game::HEIGHT) / float(backTex.getSize().y));
}


void SaveSelectionScene::update(float dt)
{
	//bs.update(dt);
}

void SaveSelectionScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape) {
		exit = true;
		next = new MenuScene();
	}
	else
		bs.onKeyPress(key);
}

std::vector<std::string> SaveSelectionBS::getSaveNames()
{
	std::vector<std::string> vs = Save::getSaves();
	int MAXS = Save::MAXSAVES;
	if (vs.size() >= MAXS)
		return std::vector<std::string>(vs.begin(), vs.begin() + MAXS);
	while (vs.size() < MAXS)
		vs.push_back("---");
	return vs;
}

SaveSelectionBS::SaveSelectionBS(SaveSelectionScene* parent)
	: parent(parent), ButtonSet(getSaveNames(), sf::FloatRect(50, 60, 300, 480))
{
	for (int i = Save::getSaves().size(); i < Save::MAXSAVES; i++) {
		buttons[i].setEnabled(false);
		buttons[i].setPaddingTop(-10);
	}
}

void SaveSelectionBS::finsihedSelection(int selected)
{
	if (Globals::save != nullptr)
		delete Globals::save;
	Globals::save = new Save(Save::getSaves().at(selected), true);
	Game::curent()->setNextScene(true, new WalkingScene("johnson_classroom"));
}
