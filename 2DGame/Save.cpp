#include "Save.h"
#include <fstream>
#include <sstream>

const int Save::MAXINT = 500;

std::string Save::gets(std::string n)
{
	if (strings.find(n) == strings.end())
		strings[n] = "";
	return strings[n];
}

void Save::sets(std::string n, std::string v)
{
	strings[n] = v;
}

int Save::geti(std::string n)
{
	if (ints.find(n) == ints.end())
		ints[n] = 0;
	return ints[n];
}

void Save::seti(std::string n, int v)
{
	ints[n] = v;
}

Save::Save(std::string savename)
{
	name = savename;
	filepath = "Files/saves/" + savename + "/";

	std::ifstream fin(filepath+"text.data");
	std::string s, name, val;
	while (!fin.eof()) {
		std::getline(fin, s);
		int x = s.find('=');
		if (x == -1)
			continue;
		name = s.substr(0, x);
		val = s.substr(x + 1);
		strings.insert(std::make_pair(name, val));
	}

	fin.close();
	fin.open(filepath + "numbers.data");
	while (!fin.eof()) {
		std::getline(fin, s);
		int x = s.find('=');
		if (x == -1)
			continue;
		name = s.substr(0, x);
		val = s.substr(x + 1);
		int in = 0;
		std::istringstream(val) >> in;
		ints.insert(std::make_pair(name, in));
	}
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
