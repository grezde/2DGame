#pragma once
#include "Globals.h"

class Item
{
public:
	std::string displayName;
	std::string type;
	std::vector<int> stats;
	std::string info;
};

class Inventory
{
private:
	static std::map<std::string, Item> items;

public:
	static const int SLOTS;

public:
	static void readFiles();
	static bool addToInventory(std::string item, int count = 0);	
	static std::vector<std::string> getFormatedInventory();
};

