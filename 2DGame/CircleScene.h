#pragma once
#include "Scene.h"

class CircleScene : public Scene
{
private:
	sf::CircleShape shape;

public:
	virtual void init() override;
	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

