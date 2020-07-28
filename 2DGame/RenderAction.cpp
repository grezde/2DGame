#include "RenderAction.h"
#include "Room.h"

RenderAction::RenderAction(std::vector<std::string> data)
	: Action(data)
{
	tex = new sf::Texture();
	if (data[1][0] == 'b')
		back = true;
	else
		back = false;
}

RenderAction::~RenderAction()
{
	delete tex;
}

void RenderAction::addLocation(int x, int y)
{
	if (!loaded) {
		tex->loadFromFile(room->filepath() + data[0]);
		loaded = true;
	}
	sf::Sprite sp;
	sp.setTexture(*tex);
	sp.setScale(Room::SCALE, Room::SCALE);
	sp.setOrigin(0, tex->getSize().y);
	sprites.push_back(sp);
	igPos.push_back(sf::Vector2f(x, y+1));
}

void RenderAction::drawBackground(sf::RenderWindow* window)
{
	if (!back)
		return;
	for (auto& sp : sprites)
		window->draw(sp);
}

void RenderAction::drawForeground(sf::RenderWindow* window)
{
	if (back)
		return;
	for (auto& sp : sprites)
		window->draw(sp);
}

void RenderAction::hlPointMoved()
{
	for (int i = 0; i < sprites.size(); i++)
		sprites[i].setPosition(room->getPosOnScreen(igPos[i]));
}
