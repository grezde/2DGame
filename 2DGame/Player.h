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
	int emoteNumber;

	float timeSinceStopped;
	sf::Vector2f pos;
	sf::Vector2i nextCoords;
	Room* room;

	bool pWalking = false;

public:
	static const float SCALE;
	static const float STEPSPS;
	static const float SPEED;
	static const sf::Vector2f BOUNDING_BOX[4];
	static const float EMOTE_SCALE;

private:
	void setTexCoords(int i, int j);

public:
	Player(Room* room);

	void setEmote(int number);
	inline sf::Vector2i lookingAt() { return nextCoords; };
	inline bool walking() { return pWalking; }
	inline sf::Vector2f position() { return pos; }
	inline void setPosition(sf::Vector2f pos) { this->pos = pos; }

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};

