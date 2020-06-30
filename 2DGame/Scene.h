#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
	virtual void init() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
	virtual void update(float dt) = 0;
};

