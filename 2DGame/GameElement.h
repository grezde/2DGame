#pragma once
#include <SFML/Graphics.hpp>

class IGameElement : public sf::Drawable {
public:
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void update(float dt) = 0;
};

class TwoStateGameElement {
public:
	virtual void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(float dt) = 0;
};