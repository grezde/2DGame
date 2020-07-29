#pragma once
#include "Action.h"
#include "Globals.h"

class ConditionAction : public Action
{
private:
	std::map<int, Action*> actions;
	std::string varname;
	
	Action* curent = nullptr;
	int curentindex = Save::MAXINT+1;

public:
	ConditionAction(std::vector<std::string> data);
	~ConditionAction();

	void setRoom(Room* roomPtr);
	void setPlayer(Player* playerPtr);

	void onRead(std::istream& fin);
	void update(float dt);

	void addLocation(int x, int y);
	void preinit();
	void init();
	void postinit();
	void drawBackground(sf::RenderWindow* window);
	void drawForeground(sf::RenderWindow* window);
	void trigger();
	void hlPointMoved();
	void reinitScene();
	
};

