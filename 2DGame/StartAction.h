#pragma once
#include "Action.h"

class StartAction : public Action
{
private:
	float startx, starty;
	static bool takeAction;

public:
	StartAction(std::vector<std::string> data) : Action(data) {};

	void preinit();
	void addLocation(int x, int y);
	void init();

	inline static void stopActing() { takeAction = false; }
};

