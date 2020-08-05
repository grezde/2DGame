#pragma once
#include <string>
#include <map>
#include <vector>

class Save
{
private:
	std::map<std::string, std::string> strings;
	std::map<std::string, int> ints;
	std::string name, filepath;

	bool modifications;

	static std::vector<std::string> saves;
	static bool loadedSaves;

public:
	static const int MAXINT;
	static const int MAXSAVES;

public:
	std::string gets(std::string n);
	void sets(std::string n, std::string v);
	bool hass(std::string n);
	void rems(std::string n);

	int geti(std::string n);
	void seti(std::string n, int v);
	bool hasi(std::string n);
	void remi(std::string n);

	std::string get(std::string n);

public:
	Save(std::string savename, bool exists = true);
	
	static std::vector<std::string>& getSaves();

	void loadToFile();
	inline bool wasModified() { return modifications; }
};

