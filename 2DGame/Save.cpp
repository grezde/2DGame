#include "Save.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "SavePopupScene.h"
#include "Game.h"
#include <ctime>

const int Save::MAXINT = 500;
const int Save::MAXSAVES = 5;
bool Save::loadedSaves = false;
std::vector<std::string> Save::saves = std::vector<std::string>();
std::vector<SaveMetadata> Save::metas = std::vector<SaveMetadata>();

std::string Save::gets(std::string n)
{
	if (strings.find(n) == strings.end())
		return "";
	return strings[n];
}

void Save::sets(std::string n, std::string v)
{
	modifications = true;
	strings[n] = v;
}

bool Save::hass(std::string n)
{
	return !(strings.find(n) == strings.end());
}

void Save::rems(std::string n)
{
	if (strings.find(n) == strings.end())
		return;
	modifications = true;
	strings.erase(n);
}

int Save::geti(std::string n)
{
	if (ints.find(n) == ints.end())
		return 0;
	return ints[n];
}

void Save::seti(std::string n, int v)
{
	modifications = true;
	ints[n] = v;
}

bool Save::hasi(std::string n)
{
	return !(ints.find(n) == ints.end());
}

void Save::remi(std::string n)
{
	if (ints.find(n) == ints.end())
		return;
	modifications = true;
	ints.erase(n);
}

std::string Save::get(std::string n)
{
	if (strings.find(n) == strings.end() && ints.find(n) == ints.end())
		return "";
	if (strings.find(n) != strings.end())
		return strings[n];
	return (std::ostringstream() << ints[n]).str();
}

Save::Save(std::string savename, bool exists)
{
	modifications = false;
	name = savename;
	filepath = "Files/saves/" + savename + "/";

	if (!exists) {
		sets("save_name", savename);
		std::filesystem::create_directory("Files/saves/" + savename);
		loadToFile(false);
		Save::getSaves();
		metaindex = saves.size();
		saves.push_back(savename);
		metas.push_back(SaveMetadata(savename, false));
		std::ofstream fout("Files/saves/saves.txt");
		fout << saves.size() << "\n";
		for (std::string s : saves)
			fout << s << "\n";
		return;
	}
	else
		metaindex = std::find(saves.begin(), saves.end(), savename) - saves.begin();

	std::ifstream fin(filepath+"text.data");
	std::string s, name, val;
	while (!fin.eof()) {
		std::getline(fin, s);
		int x = s.find('=');
		if (x == -1)
			continue;
		name = s.substr(0, x);
		val = s.substr(x + 1);
		strings.insert(std::pair<std::string, std::string>(name, val));
	}

	fin.close();
	fin.open(filepath + "number.data");
	while (!fin.eof()) {
		std::getline(fin, s);
		int x = s.find('=');
		if (x == -1)
			continue;
		name = s.substr(0, x);
		val = s.substr(x + 1);
		int in = 0;
		std::istringstream(val) >> in;
		ints.insert(std::pair<std::string, int>(name, in));
	}
}

std::vector<std::string>& Save::getSaves()
{
	if (!loadedSaves) {
		loadedSaves = true;
		std::ifstream fin("Files/saves/saves.txt");
		int n; std::string s;
		fin >> n;
		for (int i = 0; i < n; i++) {
			fin >> s;
			saves.push_back(s);
			metas.push_back(SaveMetadata(s, true));
		}
	}
	return saves;
}

SaveMetadata& Save::getMetadata(int index)
{
	return metas[index];
}

void Save::deleteSave(std::string name)
{

}

void Save::loadToFile(bool saveImage)
{
	modifications = false;

	sf::RenderTexture rt;
	rt.create(Game::WIDTH, Game::HEIGHT);
	rt.clear();
	rt.draw(*Game::curent());
	rt.display();
	delete metas[metaindex].tex;
	metas[metaindex].tex = new sf::Texture(rt.getTexture());
	metas[metaindex].tex->copyToImage().saveToFile(filepath + "thumbnail.png");

	std::ofstream fout(filepath + "text.data");
	for (auto ps : strings)
		fout << ps.first << "=" << ps.second << "\n";
	
	fout.close();
	fout.open(filepath + "number.data");
	for (auto pi : ints)
		fout << pi.first << "=" << pi.second << "\n";

	metas[metaindex].seconds += int(clock.getElapsedTime().asSeconds());
	clock.restart();
	fout.close();
	fout.open(filepath + "meta.data");
	fout << metas[metaindex].day << " " << metas[metaindex].month << " " << metas[metaindex].year << "\n";
	fout << metas[metaindex].seconds;
}

std::string SaveMetadata::getMonth(int i)
{
	switch (i)
	{
	case 1: return "Ianuarie";
	case 2: return "Februarie";
	case 3: return "Martie";
	case 4: return "Aprilie";
	case 5: return "Mai";
	case 6: return "Iunie";
	case 7: return "Iulie";
	case 8: return "August";
	case 9: return "Septmebrie";
	case 10: return "Octombie";
	case 11: return "Noiembrie";
	case 12: return "Decembrie";
	default: return "?????";
	}
}

SaveMetadata::SaveMetadata(std::string savename, bool exists)
{
	if (exists) {
		std::ifstream fin("Files/saves/" + savename + "/meta.data");
		fin >> day >> month >> year;
		fin >> seconds;
		tex = new sf::Texture();
		tex->loadFromFile("Files/saves/" + savename + "/thumbnail.png");
	}
	else {
		seconds = 0;
		std::time_t t = std::time(0);
		std::tm now;
		localtime_s(&now, &t);
		year = 1900+now.tm_year;
		month = now.tm_mon + 1;
		day = now.tm_mday;
	}
}

std::string SaveMetadata::getDate()
{
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(2) << day << " " << getMonth(month) << " " << year;
	return oss.str();
}

std::string SaveMetadata::getTime()
{
	std::ostringstream oss;
	int min = seconds / 60;
	int hrs = min / 60;
	oss << hrs << ":";
	oss << std::setfill('0') << std::setw(2) << min % 60 << ":";
	oss << std::setfill('0') << std::setw(2) << seconds % 60;
	return oss.str();
}
