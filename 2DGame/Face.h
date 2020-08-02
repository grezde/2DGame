#pragma once
#include "Scene.h"

class Face :
	public IGameElement
{
private:
	sf::Texture tex;
	sf::Sprite spr;

	bool active;
	float time=0;
	int i=0;

public:
	static const float INTERVAL;

private:
	void setDrawing(int i);

public:
	Face(std::string name);

	void setPosition(float x, float y);
	void setScale(float s);
	void setActive(bool a);

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

