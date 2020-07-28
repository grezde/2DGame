#pragma once
#include "Action.h"

class ConditionAction : public Action
{
private:
	std::map<int, Action*> actions;
	std::string varname;
	
	Action* curent;
	int curentindex;

public:
	ConditionAction(std::vector<std::string> data);
	~ConditionAction();

	virtual void onRead(std::ifstream& fin);

	virtual void addLocation(int x, int y) { for (auto p : actions) p.second->addLocation(x, y); }

	virtual void preinit() { for (auto p : actions) p.second->preinit(); }
	virtual void init() { for (auto p : actions) p.second->init(); }
	virtual void postinit() { for (auto p : actions) p.second->postinit(); }

	virtual void draw(sf::RenderWindow* window) { if (curent) curent->draw(window); };

	virtual void trigger() { if (curent) curent->trigger(); };

	virtual void hlPointMoved() { if (curent) curent->hlPointMoved(); };

	virtual void update(float dt);
};

