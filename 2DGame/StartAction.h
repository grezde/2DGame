#pragma once
#include "Action.h"

class StartAction : public Action
{
private:
	float startx, starty;

public:
	StartAction(std::vector<std::string> data) : Action(data) {};

	void addLocation(int x, int y);
	void init();
};

