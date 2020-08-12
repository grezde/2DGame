#pragma once
#include "ConditionParser.h"

class VariableConditionParser
	: public IntervalConditionParser
{
private:
	std::string varname;

public:
	VariableConditionParser(std::string text);

	virtual int getChoice() override;
};

