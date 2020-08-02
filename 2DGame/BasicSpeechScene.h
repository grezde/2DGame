#pragma once
#include "Scene.h"
#include "SpeechManager.h"

class BasicSpeechScene
	: public Scene, public SpeechManager
{
public:
	static const float INTERVAL;
	static const float FAST_INTERVAL;
	static const float LONG_INTERVAL;
	static const float SELECTION_INTERVAL;

protected:
	sf::Color textColor;
	sf::Color selectedColor; 

	sf::Text label;
	sf::Text submitlabel;
	std::vector<sf::Text> optlabs;
	int selectedOptionIndex;
	float sinceLastPress;

public:
	BasicSpeechScene(std::vector<std::string> lines);
	BasicSpeechScene(std::string sequenceFilename);

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;

	virtual void styleDisplayText(sf::Text& t) = 0;
	virtual void styleOptionsText(int i, sf::Text& t) = 0;
	virtual void stylePromptText(sf::Text& t) = 0;

	virtual void onTextEntered(char character) override;
};

