#include <fstream>
#include <iostream>
#include "Room.h"
#include "Game.h"

const float Room::SCALE = 4.0f;
const float Room::PIXPM = 16;

void Room::parseFile()
{
	std::ifstream fin(roomPath + "format.txt");
	fin >> rHeight >> rWidth;

	data = new int[rWidth * rHeight];
	int maxtype = 0;
	for (int i = 0; i < rHeight; i++)
		for (int j = 0; j < rWidth; j++) {
			fin >> data[i * rWidth + j];
			if (data[i * rWidth + j] > maxtype)
				maxtype = data[i * rWidth + j];
		}

	types = std::vector<Type>(maxtype + 1);
	for (int i = 0; i <= maxtype; i++) {
		int typeNum, nrActions;
		fin >> typeNum;
		fin >> types[typeNum].solid >> nrActions;
		for (int j = 0; j < nrActions; j++)
			types[typeNum].actions.push_back(Action::readFromStream(fin));
	}
}

Room::Room(std::string name)
{
	roomName = name;
	roomPath = "files/rooms/" + name + "/";
	parseFile();

	tex.loadFromFile(roomPath + "image.png");
	spr.setTexture(tex);
	spr.setScale(SCALE, SCALE);
	spr.setPosition(0, 0);
}

Room::~Room()
{
	delete[] data;
	for (auto type : types)
		for (auto action : type.actions)
			delete action;
}

void Room::setPlayer(Player* player)
{
	for (auto type : types)
		for (auto action : type.actions) {
			action->setRoom(this);
			action->setPlayer(player);
		}

	for (auto type : types)
		for (auto action : type.actions)
			action->preinit();
	
	for (int i = 0; i < rWidth * rHeight; i++)
		for (auto action : types[data[i]].actions)
			action->addLocation(i % rWidth, i / rWidth);

	for (auto type : types)
		for (auto action : type.actions)
			action->init();

	for (auto type : types)
		for (auto action : type.actions)
			action->postinit();
}

bool Room::positionValid(sf::Vector2f pos)
{
	if (pos.x < 0 || pos.x > rWidth)
		return false;
	if (pos.y < 0 || pos.y > rHeight)
		return false;

	int type = data[int(pos.y) * rWidth + int(pos.x)];
	int solid = types[type].solid;
	if (solid == 0)
		return true;
	if (solid == 1)
		return false;
	sf::Vector2i posi(pos.x, pos.y);
	sf::Vector2f offset(pos.x - float(posi.x), pos.y - float(posi.y));
	switch (solid)
	{ //solid in
	case 2: return offset.x < 0.5f; //dreapta
	case 3: return offset.x > 0.5f; //stanga
	case 4: return offset.y < 0.5f; //jos
	case 5: return offset.y > 0.5f; //sus
	case 6: return offset.x + offset.y < 1.0f; //dreapta jos
	case 7: return offset.x + offset.y > 1.0f; //stanga sus
	case 8: return 1.0f - offset.x + offset.y < 1.0f; //stanga jos
	case 9: return 1.0f - offset.x + offset.y > 1.0f; //dreapta sus
	}
	return true;
}

sf::Vector2f Room::projectSpeed(sf::Vector2f oldPos, sf::Vector2f newPos)
{
	sf::Vector2f vel = newPos - oldPos;
	sf::Vector2i oldPosI(oldPos.x, oldPos.y);
	sf::Vector2i newPosI(newPos.x, newPos.y);
	sf::Vector2f offOld(oldPos.x - float(oldPosI.x), oldPos.y - float(oldPosI.y));
	sf::Vector2f offNew(newPos.x - float(newPosI.x), newPos.y - float(newPosI.y));

	if (newPos.x < 0 || newPos.x > rWidth)
		vel.x = 0;
	if (newPos.y < 0 || newPos.y > rHeight)
		vel.y = 0;
	if (newPos.x < 0 || newPos.x > rWidth || newPos.y < 0 || newPos.y > rHeight)
		return vel;

	int solid = types[data[newPosI.y * rWidth + newPosI.x]].solid;
	if (solid == 0)
		return vel;

	bool changedBlock = oldPosI.x != newPosI.x || oldPosI.y != newPosI.y;

	if (solid == 2 || solid == 3 && oldPosI.x == newPosI.x) {
		bool atTheEdge = (offNew.x > 0.5f && offOld.x < 0.5f) || (offNew.x < 0.5f && offOld.x > 0.5f);
		if (atTheEdge) {
			vel.x = 0;
			return vel;
		}
	}
	if (solid == 4 || solid == 5 && oldPosI.y == newPosI.y) {
		bool atTheEdge = (offNew.y > 0.5f && offOld.y < 0.5f) || (offNew.y < 0.5f && offOld.y > 0.5f);
		if (atTheEdge) {
			vel.y = 0;
			return vel;
		}
	}
	
	int typeX = data[oldPosI.y * rWidth + newPosI.x];
	int typeY = data[newPosI.y * rWidth + oldPosI.x];
	if (types[typeX].solid)
		vel.x = 0;
	if (types[typeY].solid)
		vel.y = 0;
	return vel;
	return vel;
}

void Room::setCenterPosition(sf::Vector2f pos)
{
	sf::Vector2f beg;
	float hw = Game::WIDTH / PIXPM / SCALE / 2.0f;
	float hh = Game::HEIGHT / PIXPM / SCALE / 2.0f;

	if (pos.x <= hw)
		beg.x = 0;
	else if (pos.x >= rWidth - hw)
		beg.x = rWidth - 2 * hw;
	else
		beg.x = pos.x - hw;
	
	if (pos.y <= hh)
		beg.y = 0;
	else if (pos.y >= rHeight - hh)
		beg.y = rHeight - 2 * hh;
	else
		beg.y = pos.y - hh;

	spr.setPosition(-PIXPM * SCALE * beg);
	hlPoint = pos;

	for (auto type : types)
		for (auto action : type.actions)
			if(action != nullptr)
				action->hlPointMoved();
}

sf::Vector2f Room::getPosOnScreen(sf::Vector2f pos)
{
	float hw = Game::WIDTH / PIXPM / SCALE / 2.0f;
	float hh = Game::HEIGHT / PIXPM / SCALE / 2.0f;

	sf::Vector2f screen;
	
	if (hlPoint.x <= hw)
		screen.x = pos.x;
	else if (hlPoint.x >= rWidth - hw)
		screen.x = 2*hw + pos.x - rWidth;
	else
		screen.x = hw + pos.x - hlPoint.x;

	if (hlPoint.y <= hh)
		screen.y = pos.y;
	else if (hlPoint.y >= rHeight - hh)
		screen.y = 2*hh + pos.y - rHeight;
	else
		screen.y = hh + pos.y - hlPoint.y;

	screen = screen * PIXPM * SCALE;
	return screen;
}

void Room::drawBackground(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spr, states);
	for (auto type : types)
		for (auto action : type.actions)
			action->drawBackground(target, states);
}

void Room::drawForeground(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto type : types)
		for (auto action : type.actions)
			action->drawForeground(target, states);
}

void Room::update(float dt)
{
	for (auto type : types)
		for (auto action : type.actions)
			action->update(dt);
}

void Room::reinitScene()
{
	for (Type& t : types)
		for (Action* a : t.actions)
			a->reinitScene();
}

void Room::onKeyPress(sf::Keyboard::Key k)
{
	for (Type& t : types)
		for (Action* a : t.actions)
			a->onKeyPress(k);
}
