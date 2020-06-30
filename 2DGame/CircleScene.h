#pragma once
#include "Scene.h"

class CircleScene : public Scene
{
private:
	sf::CircleShape shape;

public:
	virtual void onKeyPress(sf::Keyboard::Key key);

	virtual void init() override;
	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

