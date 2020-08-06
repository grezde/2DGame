#pragma once
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp> 

class SaveMetadata
{
public:
	int day, month, year;
	int seconds;
	sf::Texture* tex = nullptr;

private:
	std::string getMonth(int i);

public:
	SaveMetadata(std::string savename, bool exists);
	std::string getDate();
	std::string getTime();
};

class Save
{
private:
	std::map<std::string, std::string> strings;
	std::map<std::string, int> ints;
	std::string name, filepath;

	bool modifications;
	sf::Clock clock;
	int metaindex;

	static std::vector<std::string> saves;
	static std::vector<SaveMetadata> metas;
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
	static SaveMetadata& getMetadata(int index);
	static void deleteSave(std::string name);

	void loadToFile(bool saveImage);
	inline bool wasModified() { return modifications; }
	inline std::string saveName() { return name; }
};

