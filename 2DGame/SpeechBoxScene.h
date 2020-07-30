#pragma once
#include <vector>
#include "Scene.h"
#include "SpeechManager.h"

class SpeechBoxScene : public Scene, public SpeechManager
{
private:
	sf::Texture boxTex;
	sf::Sprite boxSpr;

	sf::Text label;
	std::vector<sf::Text> optlabs;
	int selectedOptionIndex;
	float sinceLastPress;

public:
	static const float SCALE;
	static const float INTERVAL;
	static const float FAST_INTERVAL;
	static const float SELECTION_INTERVAL;

	static const float LINE_SPACING;
	static const float PADDING_X;
	static const float PADDING_Y;
	static const float CHOICE_PADDING_X;
	static const float CHOICE_PADDING_Y;
	static const int CHAR_SIZE;

public:
	SpeechBoxScene(std::vector<std::string> data);
	
	void draw(sf::RenderWindow* window);
	void update(float dt);
};

