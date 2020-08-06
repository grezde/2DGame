#include "PopupScene.h"
#include "Globals.h"
#include "Game.h"

void PopupScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform tr = sf::Transform::Identity;
	tr.translate(Game::WIDTH - x, 0);
	states.transform = states.transform * tr;
	
	normalDraw(target, states);
}

PopupScene::PopupScene()
{
	updateDown = true;
}

void PopupScene::update(float dt)
{
	if (t < time1)
		x = width * Globals::easeFunction(t / time1, false, true);
	else if (t - time1 < time2)
		x = width;
	else if (t - time1 - time2 < time3)
		x = width * Globals::easeFunction((time1 + time2 + time3 - t) / time3, false, true);
	else
		exit = true;
	t += dt;
}