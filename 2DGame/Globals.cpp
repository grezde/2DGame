#include "Globals.h"

Save* Globals::save = nullptr;
sf::Font* Globals::font = nullptr;
sf::Texture* Globals::popupBoxTex = nullptr;

float Globals::easeFunction(float frac, bool in, bool out)
{
	if (frac < 0.5f && in)
		return 2 * frac * frac;
	else if (frac > 0.5f && out)
		return 0.5f + 2 * (frac - 0.5f) * (1.5f - frac);
	return frac;
}
