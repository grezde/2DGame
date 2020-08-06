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
	if(state == 1)
		target.draw(cbs, states);
	target.draw(thumbSpr, states);
	target.draw(dateLabel, states);
	target.draw(timeLabel, states);
}

SaveSelectionScene::SaveSelectionScene()
	: bs(this), cbs(this)
{
	backTex.loadFromFile("Files/global/mech_board.png");
	backSpr.setTexture(backTex);
	backSpr.setScale(float(Game::WIDTH) / float(backTex.getSize().x), float(Game::HEIGHT) / float(backTex.getSize().y));
	thumbSpr.setPosition(400, 60);
	thumbSpr.setScale(0.4f, 0.4f);
	dateLabel.setFont(*Globals::font);
	dateLabel.setPosition(400, 315);
	dateLabel.setCharacterSize(20);
	dateLabel.setFillColor(sf::Color::White);
	dateLabel.setOutlineColor(sf::Color::Black);
	dateLabel.setOutlineThickness(2);
	timeLabel.setFont(*Globals::font);
	timeLabel.setPosition(400, 350);
	timeLabel.setCharacterSize(20);
	timeLabel.setFillColor(sf::Color::White);
	timeLabel.setOutlineColor(sf::Color::Black);
	timeLabel.setOutlineThickness(2);
}

void SaveSelectionScene::update(float dt)
{
}

void SaveSelectionScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape) {
		if (state == 1)
			state = 0;
		else {
			exit = true;
			next = new MenuScene();
		}
	}
	else if (state == 0)
		bs.onKeyPress(key);
	else
		cbs.onKeyPress(key);
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
	: parent(parent), ButtonSet(getSaveNames(), sf::FloatRect(50, 60, 300, 480), 0.25f)
{
	for (int i = Save::getSaves().size(); i < Save::MAXSAVES; i++) {
		buttons[i].setEnabled(false);
		buttons[i].setPaddingTop(-10);
	}
	changedSelection(0);
}

void SaveSelectionBS::finsihedSelection(int selected)
{
	parent->state = 1;
}

void SaveSelectionBS::changedSelection(int selected)
{
	SaveMetadata& met = Save::getMetadata(selected);
	parent->thumbSpr.setTexture(*(met.tex));
	parent->dateLabel.setString("Data creatiei : " + met.getDate());
	parent->timeLabel.setString("Timp de joc : " + met.getTime());
}

SaveConfirmationBS::SaveConfirmationBS(SaveSelectionScene* parent)
	: parent(parent), ButtonSet({ "Play", "Delete" }, sf::FloatRect(475, 380, 200, 160), 0.2f)
{
}

void SaveConfirmationBS::finsihedSelection(int selected)
{
	if (selected == 0) {
		if (Globals::save != nullptr)
			delete Globals::save;
		Globals::save = new Save(Save::getSaves().at(selected), true);
		Globals::save->seti("coords_from_save", 1);
		std::string lastRoom = Globals::save->gets("current_room");
		parent->exit = true;
		parent->next = new WalkingScene(lastRoom);
	}
}
