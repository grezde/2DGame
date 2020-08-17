#include "Globals.h"
#include "Inventory.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include "ConditionParser.h"

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
		if (Globals::save == nullptr) {
			std::cout << "   -> No save file.\n";
			continue;
		}
		if (words[0] == ":") {
			ConditionParser* cp = ConditionParser::getParser(line.substr(2));
			if (cp->getChoice())
				std::cout << "   = true\n";
			else
				std::cout << "   = false\n";
		}
		else if (words[0] == "inv") {
			if (words.size() == 2) {
				if (words[1] == "clear") {
					Inventory::clear();
					std::cout << "   => Inventory cleared.\n";
					continue;
				}
			}
			std::cout << "   -> Uknown inventory command.\n";
		}
		else
			std::cout << "   -> Uknown command.\n";
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
