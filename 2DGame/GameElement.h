#pragma once
#include <SFML/Graphics.hpp>

class IGameElement : public sf::Drawable {
public:
	virtual void update(float dt) = 0;
};

class TwoStateGameElement {
public:
	virtual void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void update(float dt) = 0;
};

class IKeyListener : public sf::Drawable {
public:
	virtual void onKeyPress(sf::Keyboard::Key key) = 0;
};