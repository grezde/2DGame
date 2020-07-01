#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Room;

class Player : public IGameElement
{
private:
	sf::Texture tex;
	sf::Sprite spr;
	
	sf::Texture emoteTex;
	sf::Sprite emoteSpr;
	bool drawEmote;

	float timeSinceStopped;
	sf::Vector2f pos;
	Room* room;

public:
	static const float SCALE;
	static const float STEPSPS;
	static const float SPEED;
	static const sf::Vector2f BOUNDING_BOX[4];
	static const float EMOTE_SCALE;

private:
	void setTexCoords(int i, int j);

public:
	Player(sf::Vector2i startPos, Room* room);

	void setEmote(int number);

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

