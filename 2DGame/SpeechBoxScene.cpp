#include "SpeechBoxScene.h"
#include "Game.h"
#include <iostream>

const float SpeechBoxScene::SCALE = 0.8f;

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

	boxTex.loadFromFile("Files/global_pictures/speech_box.png");
	boxSpr.setTexture(boxTex);
	boxSpr.setOrigin(boxTex.getSize().x / 2, boxTex.getSize().y);
	boxSpr.setScale(SCALE, SCALE);
	boxSpr.setPosition(Game::WIDTH / 2, Game::HEIGHT);
}

void SpeechBoxScene::draw(sf::RenderWindow* window)
{
	window->draw(boxSpr);
}

void SpeechBoxScene::update(float dt)
{

}
