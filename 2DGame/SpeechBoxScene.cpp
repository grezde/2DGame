#include "SpeechBoxScene.h"
#include "Game.h"
#include <iostream>

const float SpeechBoxScene::SCALE = 0.8f;
const float SpeechBoxScene::INTERVAL = 0.05f;
const float SpeechBoxScene::FAST_INTERVAL = 0.02f;
const float SpeechBoxScene::BETWEEN_LINES_PAUSE = 0.6f;
const float SpeechBoxScene::PADDING_X = 25;
const float SpeechBoxScene::PADDING_Y = 25;
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

	for (auto line : lines)
		std::cout << line << "\n";

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
	std::cout << x << " " << y << "\n";
	label.setPosition(x, y);
	label.setString("muie psd");
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

	timeSinceLast += dt;
	while (timeSinceLast > interval) {
		timeSinceLast -= interval;
		
		if (index == lines.size()) {
			exit = true;
			break;
		}

		if (untilNow.size() == lines[index].size()) {
			index++;
			timeSinceLast -= BETWEEN_LINES_PAUSE;
			untilNow.clear();
			break;
		}

		untilNow += lines[index][untilNow.size()];
		label.setString(untilNow);
	}
}
