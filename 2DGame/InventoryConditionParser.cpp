#include "InventoryConditionParser.h"
#include "Inventory.h"
#include <sstream>

InventoryConditionParser::InventoryConditionParser(std::string text)
{
	alreadyDone = false;
	third = 1;
	std::istringstream(text) >> first >> second >> third;
}

int InventoryConditionParser::getChoice()
{
	if(alreadyDone)
		return -1;
	alreadyDone = true;
	if (first == "give") {
		return Inventory::addToInventory(second, third);
	}
	else if (first == "remove") {
		int x;
		std::istringstream(second) >> x;
		return Inventory::removeInventory(x);
	}
}
