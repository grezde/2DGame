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
	virtual void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const;
	void hlPointMoved();

};

