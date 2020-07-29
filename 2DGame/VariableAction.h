#pragma once
#include "Action.h"

class VariableAction : public Action
{
private:
	bool relative;
	int amount;
	std::string name;

public:
	VariableAction(std::vector<std::string> data);
	void trigger();
};

