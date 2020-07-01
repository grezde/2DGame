#pragma once
#include "Action.h"
#include <vector>

class RenderAction : public Action
{
private:
	sf::Texture tex;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Vector2f> igPos;

public:
	RenderAction(std::vector<std::string> data) : Action(data) {};

	void addLocation(int x, int y);
	void draw(sf::RenderWindow* window);
	void hlPointMoved();

};

