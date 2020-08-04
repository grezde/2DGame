#include "Item.h"
#include <sstream>
#include <fstream>
#include "Inventory.h"

ItemType* ItemType::getTypeClass(std::string name)
{
	return new ItemType();
}

ItemType* ItemType::readType(std::istream& stream)
{
	ItemType* t = nullptr;
	std::string  s;
	std::getline(stream, s);
	t = getTypeClass(s);
	t->name = s;
	std::getline(stream, s);
	t->stackable = (s[0] == 's');
	std::getline(stream, s);
	int a, b, c;
	std::istringstream(s) >> a >> b >> c;
	for (int i = 0; i < a; i++) {
		std::getline(stream, s);
		t->statNames.push_back(s);
	}
	for (int i = 0; i < b; i++) {
		std::getline(stream, s);
		t->metaNames.push_back(s);
	}
	for (int i = 0; i < c; i++) {
		std::getline(stream, s);
		t->useNames.push_back(s);
	}
	return t;
}

std::map<std::string, ItemType*> ItemType::readTypeFile()
{
	std::map<std::string, ItemType*> types;
	std::ifstream fin("Files/items/types.txt");
	int n;
	std::string s;
	fin >> n;
	std::getline(fin, s);
	std::getline(fin, s);
	for (int i = 0; i < n; i++) {
		ItemType* it = ItemType::readType(fin);
		std::getline(fin, s);
		types[it->name] = it;
	}
	return types;
}

Item Item::readItem(std::istream& stream, Item::typemap& types)
{
	Item t;
	std::string s, type;
	std::getline(stream, t.name);
	std::getline(stream, t.displayName);
	std::getline(stream, s);
	std::istringstream iss(s);
	iss >> type;
	t.type = types[type];
	while (!iss.eof()) {
		int x;
		iss >> x;
		t.stats.push_back(x);
	}
	std::getline(stream, t.info);
	std::getline(stream, s);
	while (!s.empty()) {
		t.info += "\n" + s;
		std::getline(stream, s);
	}
	return t;
}

std::map<std::string, Item> Item::readItemFile(Item::typemap& types)
{
	std::map<std::string, Item> items;
	std::ifstream fin("Files/items/items.txt");
	int n;
	std::string s, name;
	fin >> n;
	std::getline(fin, s);
	for (int i = 0; i < n; i++) {
		Item it = readItem(fin, types);
		items[it.name] = it;
	}
	return items;
}
