#include "Save.h"
#include <fstream>
#include <sstream>
#include <direct.h>
#include <filesystem>

const int Save::MAXINT = 500;
const int Save::MAXSAVES = 5;
bool Save::loadedSaves = false;
std::vector<std::string> Save::saves = std::vector<std::string>();

std::string Save::gets(std::string n)
{
	if (strings.find(n) == strings.end())
		return "";
	return strings[n];
}

void Save::sets(std::string n, std::string v)
{
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
	name = savename;
	filepath = "Files/saves/" + savename + "/";

	if (!exists) {
		sets("save_name", savename);
		std::filesystem::create_directory("Files/saves/" + savename);
		loadToFile();
		Save::getSaves();
		saves.push_back(savename);
		std::ofstream fout("Files/saves/saves.txt");
		fout << saves.size() << "\n";
		for (std::string s : saves)
			fout << s << "\n";
		return;
	}

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
		}
	}
	return saves;
}

void Save::loadToFile()
{
	std::ofstream fout(filepath + "text.data");
	for (auto ps : strings)
		fout << ps.first << "=" << ps.second << "\n";
	
	fout.close();
	fout.open(filepath + "numbers.data");
	for (auto pi : ints)
		fout << pi.first << "=" << pi.second << "\n";
}
