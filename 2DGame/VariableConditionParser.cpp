#include "VariableConditionParser.h"
#include "Globals.h"
#include <sstream>
#include <iostream>

VariableConditionParser::VariableConditionParser(std::string text)
{
	std::istringstream iss(text);
	iss >> varname;
	readIntervals(iss);
}

int VariableConditionParser::getChoice()
{
	if(Globals::save == nullptr)
		return -1;
	return getIntervalIndex(Globals::save->geti(varname));
}
