#pragma once
#include "Globals.h"
#include "Item.h"

class Inventory
{
private:
	static std::map<std::string, Item*> items;
	static std::map<std::string, ItemType*> types;
	static bool read;

public:
	static const int SLOTS;

public:
	static void readFiles();

	static void setMetadata(int slot, int metaSlot, int value);
	static int getMetadata(int slot, int metaSlot);
	
	static int getCount(int slot);
	static void setCount(int slot, int count);

	static Item* getItemAt(int slot);

	static std::vector<std::string> getFormatedInventory();
	static std::vector<std::string> getFormatedStats(int slot);

	static bool addToInventory(std::string item, int count = 1);
	static bool removeInventory(int slot);
	static void clear();
};

