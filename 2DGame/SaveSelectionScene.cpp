#include "SaveSelectionScene.h"
#include "Save.h"
#include "Game.h"
#include "Globals.h"
#include "WalkingScene.h"

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

void SaveSelectionScene::draw(sf::RenderWindow* window)
{
}

void SaveSelectionScene::update(float dt)
{
	if (!stoppedPressing) {
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
			stoppedPressing = true;
		return;
	}

	bs.update(dt);
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
