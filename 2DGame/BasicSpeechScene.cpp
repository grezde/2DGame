#include "BasicSpeechScene.h"
#include <iostream>

const float BasicSpeechScene::INTERVAL = 0.05f;
const float BasicSpeechScene::FAST_INTERVAL = 0.015f;
const float BasicSpeechScene::LONG_INTERVAL = 0.5f;

BasicSpeechScene::BasicSpeechScene(std::vector<std::string> lines)
	: SpeechManager(lines)
{
}

BasicSpeechScene::BasicSpeechScene(std::string sequenceFilename)
	: SpeechManager(sequenceFilename)
{
}

void BasicSpeechScene::draw(sf::RenderWindow* window)
{
	window->draw(label);
	if (state() == WritingMenuOptions || state() == Selecting)
		for (sf::Text& optlab : optlabs)
			window->draw(optlab);
	if (state() == ReadingPrompt)
		window->draw(submitlabel);
}

void BasicSpeechScene::update(float dt)
{
	if (state() == ReadingPrompt)
		interval = LONG_INTERVAL;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
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

	if (state() == ReadingPrompt) 
		submitlabel.setString(displayText());

	if (state() == WritingMenuText) {
		int n = numberOfOptions();
		if (n != optlabs.size()) {
			selectedOptionIndex = -1;
			sinceLastPress = 0;
			for (int i = 0; i < n; i++) {
				sf::Text t;
				styleOptionsText(i, t);
				optlabs.push_back(t);
			}
		}
	}

	if (state() == Selecting) {
		for (sf::Text& t : optlabs)
			t.setFillColor(textColor);
		if (selectedOptionIndex != -1) {
			optlabs[selectedOptionIndex].setFillColor(selectedColor);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				optlabs.clear();
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
				selectedOptionIndex = numberOfOptions() - 1;
			else if (selectedOptionIndex != numberOfOptions() - 1)
				selectedOptionIndex++;
		}
		sinceLastPress += dt;
	}

	if (state() == WritingMenuOptions)
		optlabs[curentOptionWriten()].setString(displayText());

	if (state() == Writing || state() == WritingMenuText || state() == WritingPromptText)
		label.setString(displayText());
}

void BasicSpeechScene::onTextEntered(char character)
{
	if (state() == ReadingPrompt)
		submitChar(character);
}
