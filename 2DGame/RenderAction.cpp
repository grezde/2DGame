#include "RenderAction.h"
#include "Room.h"

void RenderAction::addLocation(int x, int y)
{
	tex.loadFromFile(room->filepath() + data[0]);
	sf::Sprite sp;
	sp.setTexture(tex);
	sp.setScale(Room::SCALE, Room::SCALE);
	sp.setOrigin(0, tex.getSize().y);
	sprites.push_back(sp);
	igPos.push_back(sf::Vector2f(x, y+1));
}

void RenderAction::draw(sf::RenderWindow* window)
{
	for (auto sp : sprites)
		window->draw(sp);
}

void RenderAction::hlPointMoved()
{
	for (int i = 0; i < sprites.size(); i++)
		sprites[i].setPosition(room->getPosOnScreen(igPos[i]));
}
