#include "SpeechBoxScene.h"
#include "Game.h"
#include <iostream>

const float SpeechBoxScene::SCALE = 0.8f;
const float SpeechBoxScene::INTERVAL = 0.05f;
const float SpeechBoxScene::FAST_INTERVAL = 0.015f;

const float SpeechBoxScene::LINE_SPACING = 1.5f;
const float SpeechBoxScene::PADDING_X = 25;
const float SpeechBoxScene::PADDING_Y = 35;
const int SpeechBoxScene::CHAR_SIZE = 25;

sf::Font* SpeechBoxScene::font = nullptr;

SpeechBoxScene::SpeechBoxScene(std::vector<std::string> data)
{
	for (auto line : data) {
		if (line[0] == '*')
			lines.push_back(std::string(line.begin() + 2, line.end()));
		else
			lines.back() += "\n" + line;
	}

	boxTex.loadFromFile("Files/global/speech_box.png");
	boxSpr.setTexture(boxTex);
	boxSpr.setOrigin(boxTex.getSize().x / 2, boxTex.getSize().y);
	boxSpr.setScale(SCALE, SCALE);
	boxSpr.setPosition(Game::WIDTH / 2, Game::HEIGHT);

	if (font == nullptr) {
		font = new sf::Font();
		font->loadFromFile("Files/other/FFFForward.TTF");
	}
	label.setFont(*font);
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
	label.setFillColor(sf::Color::Black);
}

void SpeechBoxScene::draw(sf::RenderWindow* window)
{
	window->draw(boxSpr);
	window->draw(label);
}

void SpeechBoxScene::update(float dt)
{
	float interval;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		interval = FAST_INTERVAL;
	else
		interval = INTERVAL;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		if (finished) {
			index++;
			untilNow.clear();
			finished = false;
			if (index == lines.size()) {
				exit = true;
				return;
			}
		}

	if (finished)
		return;

	timeSinceLast += dt;
	while (timeSinceLast > interval) {
		timeSinceLast -= interval;
		
		if (untilNow.size() == lines[index].size()) {
			finished = true;
			break;
		}

		untilNow += lines[index][untilNow.size()];
		label.setString(untilNow);
	}
}
