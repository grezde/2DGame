#pragma once
#include "ConditionParser.h"

class InventoryConditionParser :
	public BooleanConditionParser
{
private:
	bool alreadyDone;
	std::string first;
	std::string second;
	int third;

public:
	InventoryConditionParser(std::string text);

	virtual int getChoice() override;

};

