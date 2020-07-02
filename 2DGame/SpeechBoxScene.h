#pragma once
#include "Scene.h"
#include <vector>

class SpeechBoxScene : public Scene
{
private:
	sf::Texture boxTex;
	sf::Sprite boxSpr;
	std::vector<std::string> lines;

	static sf::Font* font;
	sf::Text label;

	int index = 0;
	std::string untilNow;
	float timeSinceLast = 0.0f;

public:
	static const float SCALE;
	static const float INTERVAL;
	static const float FAST_INTERVAL;
	static const float BETWEEN_LINES_PAUSE;

	static const float PADDING_X;
	static const float PADDING_Y;
	static const int CHAR_SIZE;

public:
	SpeechBoxScene(std::vector<std::string> data);
	
	void draw(sf::RenderWindow* window);
	void update(float dt);
};

