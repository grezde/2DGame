#include "Inventory.h"
#include <fstream>
#include <sstream>
#include <iomanip>

std::map<std::string, Item> Inventory::items = std::map<std::string, Item>();
const int Inventory::SLOTS = 10;

void Inventory::readFiles()
{
	if (!items.empty())
		return;
	std::ifstream fin("Files/lookup/items.txt");
	int n;
	fin >> n;
	std::string name, s;
	std::getline(fin, s);
	for (int i = 0; i < n; i++) {
		Item t;
		std::getline(fin, name);
		std::getline(fin, t.displayName);
		std::getline(fin, s);
		std::istringstream iss(s);
		iss >> t.type;
		while (!iss.eof()) {
			int x;
			iss >> x;
			t.stats.push_back(x);
		}
		std::getline(fin, t.info);
		std::getline(fin, s);
		while (!s.empty()) {
			t.info += "\n" + s;
			std::getline(fin, s);
		}
		items[name] = t;
	}
}

bool Inventory::addToInventory(std::string item, int count)
{
	for (int i = 0; i < 10; i++) {
		std::string a = Globals::save->gets("inventory_slot_" + std::to_string(i));
		if (a == item) {
			int count0 = Globals::save->geti("inventory_count_" + std::to_string(i));
			Globals::save->seti("inventory_count_" + std::to_string(i), count0 + count);
			return true;
		}
		if (a.empty()) {
			Globals::save->sets("inventory_slot_" + std::to_string(i), item);
			Globals::save->seti("inventory_count_" + std::to_string(i), count);
			return true;
		}
	}
	return false;
}

std::vector<std::string> Inventory::getFormatedInventory()
{
	std::vector<std::string> vs;
	for (int i = 0; i < 10; i++) {
		std::ostringstream oss;
		int hascount = Globals::save->hasi("inventory_count_" + std::to_string(i));
		if (hascount)
			oss << std::setfill('0') << std::setw(3) << Globals::save->geti("inventory_count_" + std::to_string(i));
		else
			oss << "---";
		std::string item = Globals::save->gets("inventory_slot_" + std::to_string(i));
		if (!item.empty())
			oss << " " << items[item].displayName;
		else
			oss << " --------";
		vs.push_back(oss.str());
	}
	return vs;
}
