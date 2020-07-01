#pragma once
#include <SFML/Graphics.hpp>

class Room;
class Player;

class Action
{
protected:
	Room* room;
	Player* player;
	std::vector<std::string> data;

public:
	Action(std::vector<std::string> data) : data(data) {};

	void setRoom(Room* roomPtr) { room = roomPtr; }
	void setPlayer(Player* playerPtr) { player = playerPtr; }

	virtual void addLocation(int x, int y) {};
	virtual void draw(sf::RenderWindow* window) {};
	virtual void hlPointMoved() {};
	virtual void update(float dt) {};

};

