#pragma once
#include "Action.h"

class InventoryAction :
	public Action
{
public:
	InventoryAction(std::vector<std::string> data);

	virtual void trigger() override;
};

