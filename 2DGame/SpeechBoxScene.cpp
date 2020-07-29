#include "SpeechBoxScene.h"
#include "Game.h"
#include <iostream>

const float SpeechBoxScene::SCALE = 0.8f;
const float SpeechBoxScene::INTERVAL = 0.05f;
const float SpeechBoxScene::FAST_INTERVAL = 0.015f;
const float SpeechBoxScene::SELECTION_INTERVAL = 0.1f;

const float SpeechBoxScene::LINE_SPACING = 1.5f;
const float SpeechBoxScene::PADDING_X = 25;
const float SpeechBoxScene::CHOICE_PADDING_X = 15;
const float SpeechBoxScene::CHOICE_PADDING_Y = 10;
const float SpeechBoxScene::PADDING_Y = 35;
const int SpeechBoxScene::CHAR_SIZE = 25;

sf::Font* SpeechBoxScene::font = nullptr;

SpeechBoxScene::SpeechBoxScene(std::vector<std::string> data)
	: SpeechManager(data)
{
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
	if (state() == WritingMenuOptions || state() == Selecting)
		for (sf::Text& optlab : optlabs)
			window->draw(optlab);
}

void SpeechBoxScene::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		interval = FAST_INTERVAL;
	else
		interval = INTERVAL;
	if (state() == Pause && sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		proceed();
	
	updateState(dt);

	if (state() == Finished) {
		exit = true;
		return;
	}

	if (state() == WritingMenuText) {
		int n = numberOfOptions();
		if (n != optlabs.size()) {
			selectedOptionIndex = -1;
			sinceLastPress = 0;
			for (int i = 0; i < n; i++) {
				sf::Text t;
				t.setFont(*font);
				t.setPosition(
					label.getPosition() + sf::Vector2f(
						CHOICE_PADDING_X + float(i) / float(n) * label.getLocalBounds().width,
						CHOICE_PADDING_Y + float(label.getCharacterSize()) * label.getLineSpacing()
					));
				t.setLineSpacing(LINE_SPACING);
				t.setCharacterSize(CHAR_SIZE);
				t.setFillColor(sf::Color::Black);
				optlabs.push_back(t);
			}
		}
	}

	if (state() == Selecting) {
		for (sf::Text& t : optlabs)
			t.setFillColor(sf::Color::Black);
		if (selectedOptionIndex != -1) {
			optlabs[selectedOptionIndex].setFillColor(sf::Color(128, 0, 0));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				proceed(selectedOptionIndex);
				return;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			&& sinceLastPress > SELECTION_INTERVAL) {
			sinceLastPress = 0;
			if (selectedOptionIndex == -1)
				selectedOptionIndex = 0;
			else if (selectedOptionIndex != 0)
				selectedOptionIndex--;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			&& sinceLastPress > SELECTION_INTERVAL) {
			sinceLastPress = 0;
			if (selectedOptionIndex == -1)
				selectedOptionIndex = numberOfOptions()-1;
			else if (selectedOptionIndex != numberOfOptions()-1)
				selectedOptionIndex++;
		}
		sinceLastPress += dt;
	}

	if (state() == WritingMenuOptions)
		optlabs[curentOptionWriten()].setString(displayText());

	if(state() == Writing || state() == WritingMenuText)
		label.setString(displayText());
}
