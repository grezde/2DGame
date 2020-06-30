#pragma once
#include "Scene.h"

class SquareScene : public Scene
{
private:
	sf::RectangleShape rect;
public:
	virtual void onKeyPress(sf::Keyboard::Key key);
	virtual void init();

	virtual void draw(sf::RenderWindow* window);
	virtual void update(float dt);
};

