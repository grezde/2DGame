#pragma once
#include "Save.h"
#include <SFML/Graphics.hpp>

class Globals
{
public:
	static Save* save;
	static sf::Font* font;
	static sf::Texture* popupBoxTex;
	
public:
	static float easeFunction(float frac, bool in, bool out);
};

