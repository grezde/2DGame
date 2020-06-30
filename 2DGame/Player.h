#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Room;

class Player : public IGameElement
{
private:
	sf::Texture tex;
	sf::Sprite spr;
	float timeSinceStopped;
	sf::Vector2f pos;
	Room* room;

public:
	static const float SCALE;
	static const float STEPSPS;
	static const float SPEED;

private:
	void setTexCoords(int i, int j);

public:
	Player(sf::Vector2i startPos, Room* room);

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

