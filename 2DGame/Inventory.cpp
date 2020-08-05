#include "Inventory.h"
#include <fstream>
#include <sstream>
#include <iomanip>

std::map<std::string, Item> Inventory::items = std::map<std::string, Item>();
std::map<std::string, ItemType*> Inventory::types = std::map<std::string, ItemType*>();
const int Inventory::SLOTS = 10;
bool Inventory::read = false;

void Inventory::readFiles()
{
	if (read)
		return;
	read = true;

	types = ItemType::readTypeFile();
	items = Item::readItemFile(types);
}

void Inventory::setMetadata(int slot, int metaSlot, int value)
{
	Globals::save->seti("inventory_meta_" + std::to_string(metaSlot) + "_" + std::to_string(slot), value);
}

int Inventory::getMetadata(int slot, int metaSlot)
{
	return Globals::save->geti("inventory_meta_" + std::to_string(metaSlot) + "_" + std::to_string(slot));
}

int Inventory::getCount(int slot)
{
	return Globals::save->geti("inventory_count_" + std::to_string(slot));
}

void Inventory::setCount(int slot, int count)
{
	if (getItemAt(slot) == nullptr || !getItemAt(slot)->type->stackable)
		return;
	if (count == 0 ) {
		std::string fin = "_" + std::to_string(slot);
		Globals::save->rems("inventory_slot" + fin);
		Globals::save->remi("inventory_count" + fin);
		for (int i = 0, n=getItemAt(slot)->type->metaNames.size(); i<n; i++)
			Globals::save->remi("inventory_meta_" + std::to_string(i) + fin);
	}
	else
		Globals::save->seti("inventory_count_" + std::to_string(slot), count);
}

Item* Inventory::getItemAt(int slot)
{
	std::string a = Globals::save->gets("inventory_slot_" + std::to_string(slot));
	if (a.empty()) 
		return nullptr;
	return &items[a];
}

bool Inventory::addToInventory(std::string item, int count)
{
	for (int i = 0; i < 10; i++) {
		std::string a = Globals::save->gets("inventory_slot_" + std::to_string(i));
		if (a == item) {
			if (items[item].type->stackable) {
				int count0 = Globals::save->geti("inventory_count_" + std::to_string(i));
				Globals::save->seti("inventory_count_" + std::to_string(i), count0 + count);
			}
			return true;
		}
		if (a.empty()) {
			Globals::save->sets("inventory_slot_" + std::to_string(i), item);
			if(items[item].type->stackable)
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
			oss << std::setfill('0') << std::setw(2) << Globals::save->geti("inventory_count_" + std::to_string(i));
		else
			oss << "--";
		std::string item = Globals::save->gets("inventory_slot_" + std::to_string(i));
		if (!item.empty())
			oss << " " << items[item].displayName;
		else
			oss << " --------";
		vs.push_back(oss.str());
	}
	return vs;
}

std::vector<std::string> Inventory::getFormatedStats(int slot)
{
	std::vector<std::string> vs;
	if (getItemAt(slot) == nullptr)
		return vs;
	Item* it = getItemAt(slot);
	for (int i = 0; i < it->stats.size(); i++)
		vs.push_back(" >  " + it->type->statNames[i] + " " + std::to_string(it->stats[i]));
	for (int i = 0; i < it->type->metaNames.size(); i++)
		vs.push_back(">> " + it->type->metaNames[i] + " " + std::to_string(getMetadata(slot, i)));
	return vs;
}