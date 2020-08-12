#pragma once
#include <vector>
#include <string>
#include <istream>
#include <map>

class ItemType
{
public:
	typedef std::vector<std::string> vecstr;

	//these should all be private with getters
	//but i'm lazy
	vecstr statNames;
	vecstr metaNames;
	vecstr useNames;
	bool stackable;
	std::string name;

private:
	static ItemType* getTypeClass(std::string name);

public:
	static ItemType* readType(std::istream& stream);
	static std::map<std::string, ItemType*> readTypeFile();

	virtual void initItem(int slot) {}
	virtual void useItem(int slot, int useNumber) {}
	virtual void destroyItem(int slot) {}
};

class Item
{
public:
	typedef std::map<std::string, ItemType*> typemap;

	std::string name;
	std::string displayName;
	ItemType* type;
	std::vector<int> stats;
	std::string info;

public:
	static Item readItem(std::istream& stream, typemap& types);
	static std::map<std::string, Item> readItemFile(typemap& types);
	
};


