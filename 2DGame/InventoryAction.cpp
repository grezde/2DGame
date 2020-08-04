#include "InventoryAction.h"
#include <sstream>
#include "Inventory.h"

InventoryAction::InventoryAction(std::vector<std::string> data)
	: Action(data)
{
}

void InventoryAction::trigger()
{
	;;;
	int count = 1;
	if (data.size() == 2)
		std::istringstream(data[1]) >> count;
	Inventory::addToInventory(data[0], count);
	;;;
}
