#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

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

	virtual void onRead(std::ifstream& fin) {};
	virtual void addLocation(int x, int y) {};

	virtual void preinit() {};
	virtual void init() {};
	virtual void postinit() {};

	virtual void draw(sf::RenderWindow* window) {};
	virtual void update(float dt) {};

	virtual void trigger() {};

	virtual void hlPointMoved() {};

private:
	static Action* getActionClass(char code, std::vector<std::string> data);

public:
	static Action* readFromFile(std::ifstream& fin);
};

