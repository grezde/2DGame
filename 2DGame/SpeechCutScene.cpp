#include "SpeechCutScene.h"
#include "Globals.h"
#include "Game.h"

SpeechCutScene::SpeechCutScene(std::vector<std::string> data)
	: BasicSpeechScene(data)
{
	textColor = sf::Color(200, 200, 200);
	selectedColor = sf::Color(255, 0, 0);
	styleDisplayText(label);
	stylePromptText(submitlabel);
}

SpeechCutScene::SpeechCutScene(std::string filename)
	: BasicSpeechScene("Files/sequences/" + filename + ".txt")
{
	textColor = sf::Color(200, 200, 200);
	selectedColor = sf::Color(255, 0, 0);
	styleDisplayText(label);
	stylePromptText(submitlabel);
}

void SpeechCutScene::draw(sf::RenderWindow* window)
{
	BasicSpeechScene::draw(window);
}

void SpeechCutScene::update(float dt)
{
	BasicSpeechScene::update(dt);
}

void SpeechCutScene::styleDisplayText(sf::Text& t)
{
	label.setFont(*Globals::font);
	label.setPosition(100, 350);
	label.setString("");
	label.setLineSpacing(1.6f);
	label.setCharacterSize(26);
	label.setFillColor(textColor);
}

void SpeechCutScene::styleOptionsText(int i, sf::Text& t)
{
	t.setFont(*Globals::font);
	t.setPosition(
		100.0f + (Game::WIDTH-200.0f)/float(numberOfOptions())*float(i) + 25,
		460
	);
	t.setLineSpacing(1.6f);
	t.setCharacterSize(26);
	t.setFillColor(textColor);
}

void SpeechCutScene::stylePromptText(sf::Text& t)
{
	t.setFont(*Globals::font);
	t.setPosition(150, 460);
	t.setLineSpacing(1.6f);
	t.setCharacterSize(26);
	t.setFillColor(textColor);
}

void SpeechCutScene::styleFace(Face& face)
{
	face.setPosition(400, 225);
	face.setScale(3);
}
