#pragma once
#include <fstream>
#include "GameElement.h"

class Room;
class Player;

class Action
	: public TwoStateGameElement
{
protected:
	Room* room;
	Player* player;
	std::vector<std::string> data;

public:
	Action(std::vector<std::string> data) : data(data) {};
	Action() {};

	virtual void setRoom(Room* roomPtr) { room = roomPtr; }
	virtual void setPlayer(Player* playerPtr) { player = playerPtr; }

	virtual void onRead(std::istream& fin) {};
	virtual void addLocation(int x, int y) {};

	virtual void preinit() {};
	virtual void init() {};
	virtual void postinit() {};

	virtual void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const {}
	virtual void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const {}
	virtual void update(float dt) {}

	virtual void trigger() {};

	virtual void hlPointMoved() {};
	virtual void reinitScene() {};
	virtual void onKeyPress(sf::Keyboard::Key key) {};

private:
	static Action* getActionClass(char code, std::vector<std::string> data);

public:
	static Action* readFromStream(std::istream& fin);
};

