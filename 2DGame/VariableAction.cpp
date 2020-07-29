#include "VariableAction.h"
#include <sstream>
#include "Globals.h"

VariableAction::VariableAction(std::vector<std::string> data)
{
	name = data[0];
	std::string s;
	std::istringstream(data[1]) >> s >> amount;
	if (s == "+=")
		relative = true;
	else if (s == "-=") {
		relative = true;
		amount = -amount;
	}
	else if (s == "=")
		relative = false;
}

void VariableAction::trigger()
{
	if (relative) {
		int x = Globals::save->geti(name);
		Globals::save->seti(name, x + amount);
	}
	else
		Globals::save->seti(name, amount);
}
