#pragma once
#include "Action.h"
#include "Globals.h"
#include "ConditionParser.h"

class ConditionAction : public Action
{
private:
	std::vector<Action*> actions;
	ConditionParser* cp = nullptr;
	Action* curent = nullptr;
	
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
	virtual void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const;
	void trigger();
	void hlPointMoved();
	void reinitScene();
	void onKeyPress(sf::Keyboard::Key k);
	
};

