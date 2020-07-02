#pragma once
#include "Scene.h"
#include <vector>

class SpeechBoxScene : public Scene
{
private:
	sf::Texture boxTex;
	sf::Sprite boxSpr;
	std::vector<std::string> lines;

public:
	static const float SCALE;

public:
	SpeechBoxScene(std::vector<std::string> data);
	
	void draw(sf::RenderWindow* window);
	void update(float dt);
};

