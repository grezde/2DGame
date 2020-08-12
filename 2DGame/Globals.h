#pragma once
#include "Save.h"
#include <SFML/Graphics.hpp>
#include <thread>

class Globals
{
private:
	static std::thread* command;

public:
	static Save* save;
	static sf::Font* font;
	static sf::Texture* popupBoxTex;

private:
	static void processCommands();

public:
	static void init();
	static float easeFunction(float frac, bool in, bool out);
};

