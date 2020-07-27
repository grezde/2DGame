#pragma once
#include <string>
#include <map>

class Save
{
private:
	std::map<std::string, std::string> strings;
	std::map<std::string, int> ints;
	std::string name, filepath;

public:
	std::string gets(std::string n);
	void sets(std::string n, std::string v);

	int geti(std::string n);
	void seti(std::string n, int v);

public:
	Save(std::string savename);

	void loadToFile();
};

