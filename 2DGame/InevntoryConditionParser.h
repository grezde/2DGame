#pragma once
#include "ConditionParser.h"

class InevntoryConditionParser :
	public BooleanConditionParser
{
private:
	bool alreadyDone;
	std::string first;
	std::string second;
	int third;

public:
	InevntoryConditionParser(std::string text);

	virtual int getChoice() override;

};

