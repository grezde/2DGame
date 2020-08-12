#include "Globals.h"
#include "Inventory.h"
#include "Game.h"
#include <iostream>
#include <sstream>

Save* Globals::save = nullptr;
sf::Font* Globals::font = nullptr;
sf::Texture* Globals::popupBoxTex = nullptr;
std::thread* Globals::command = nullptr;

void Globals::processCommands()
{
	std::string line, word;
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, line);
		std::vector<std::string> words;
		std::istringstream iss(line); 
		do {
			iss >> word;
			words.push_back(word);
		} while (!iss.eof());
		if (words.size() == 0)
			continue;
		if (words[0] == "inventory") {
			if (Globals::save == nullptr) {
				std::cout << "= No save file\n";
				continue;
			}
			if (words.size() != 3)
				std::cout << " = Incomplete command\n";
			else if (words[1] == "add")
				std::cout << (Inventory::addToInventory(words[2]) ? " = Added new item\n" : " = Failed to add to inventory\n");
			else if (words[1] == "remove") {
				int slot;
				std::istringstream(words[2]) >> slot;
				std::cout << (Inventory::removeInventory(slot) ? " = Removed item\n" : " = Failed to remove from inventory\n");
			}
			else
				std::cout << " = Unknown inventory command\n";
		}
		if (words[0] == "stop") {
			Game::curent()->clearAllScenes();
			break;
		}
		if (words[0] == "save") {
			if (Globals::save == nullptr) {
				std::cout << " = No save file\n";
				continue;
			}
			Globals::save->loadToFile(true);
			std::cout << " = Saved file\n";
		}
	}
}

void Globals::init()
{
	Globals::font = new sf::Font();
	Globals::font->loadFromFile("Files/other/FFFForward.TTF");
	Globals::popupBoxTex = new sf::Texture();
	Globals::popupBoxTex->loadFromFile("Files/global/basic_popup_box.png");
	Inventory::readFiles();
	command = new std::thread(processCommands);
}

float Globals::easeFunction(float frac, bool in, bool out)
{
	if (frac < 0.5f && in)
		return 2 * frac * frac;
	else if (frac > 0.5f && out)
		return 0.5f + 2 * (frac - 0.5f) * (1.5f - frac);
	return frac;
}
