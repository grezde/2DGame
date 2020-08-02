#include "SpeechBoxScene.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>

const float SpeechBoxScene::SCALE = 0.8f;
const float SpeechBoxScene::SELECTION_INTERVAL = 0.1f;

const float SpeechBoxScene::LINE_SPACING = 1.5f;
const float SpeechBoxScene::PADDING_X = 25;
const float SpeechBoxScene::CHOICE_PADDING_X = 15;
const float SpeechBoxScene::CHOICE_PADDING_Y = 10;
const float SpeechBoxScene::PADDING_Y = 35;
const int SpeechBoxScene::CHAR_SIZE = 25;

SpeechBoxScene::SpeechBoxScene(std::vector<std::string> data)
	: BasicSpeechScene(data)
{
	boxTex.loadFromFile("Files/global/speech_box.png");
	boxSpr.setTexture(boxTex);
	boxSpr.setOrigin(boxTex.getSize().x / 2, boxTex.getSize().y);
	boxSpr.setScale(SCALE, SCALE);
	boxSpr.setPosition(Game::WIDTH / 2, Game::HEIGHT);

	textColor = sf::Color::Black;
	selectedColor = sf::Color(128, 0, 0);
	styleDisplayText(label);
}

void SpeechBoxScene::draw(sf::RenderWindow* window)
{
	window->draw(boxSpr);
	BasicSpeechScene::draw(window);
}

void SpeechBoxScene::update(float dt)
{
	BasicSpeechScene::update(dt);
}

void SpeechBoxScene::styleDisplayText(sf::Text& t)
{
	label.setFont(*Globals::font);
	float x = Game::WIDTH / 2;
	x -= float(boxTex.getSize().x) * SCALE / 2;
	x += PADDING_X;
	float y = Game::HEIGHT;
	y -= float(boxTex.getSize().y) * SCALE;
	y += PADDING_Y;
	label.setPosition(x, y);
	label.setString("");
	label.setLineSpacing(LINE_SPACING);
	label.setCharacterSize(CHAR_SIZE);
	label.setFillColor(textColor);
}

void SpeechBoxScene::styleOptionsText(int i, sf::Text& t)
{
	t.setFont(*Globals::font);
	t.setPosition(
		label.getPosition() + sf::Vector2f(
			CHOICE_PADDING_X + float(i) / float(numberOfOptions()) * label.getLocalBounds().width,
			CHOICE_PADDING_Y + float(label.getCharacterSize()) * label.getLineSpacing()
		));
	t.setLineSpacing(LINE_SPACING);
	t.setCharacterSize(CHAR_SIZE);
	t.setFillColor(textColor);
}

void SpeechBoxScene::stylePromptText(sf::Text& t)
{
}
