#pragma once
#include "Action.h"
#include <vector>

class RenderAction : public Action
{
private:
	sf::Texture* tex;
	std::vector<sf::Sprite> sprites;
	std::vector<sf::Vector2f> igPos;

	bool loaded = false;
	bool back;

public:
	RenderAction(std::vector<std::string> data);
	~RenderAction();

	void addLocation(int x, int y);
	void drawBackground(sf::RenderWindow* window);
	void drawForeground(sf::RenderWindow* window);
	void hlPointMoved();

};

