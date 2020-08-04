#pragma once
#include "Globals.h"
#include "Item.h"

class Inventory
{
private:
	static std::map<std::string, Item> items;
	static std::map<std::string, ItemType*> types;
	static bool read;

public:
	static const int SLOTS;

public:
	static void readFiles();

	void setMetadata(int slot, int metaSlot, int value);
	int getMetadata(int slot, int metaSlot);
	
	int getCount(int slot);
	void setCount(int slot, int count);

	Item* getItemAt(int slot);

	static bool addToInventory(std::string item, int count = 0);	
	static std::vector<std::string> getFormatedInventory();
};

