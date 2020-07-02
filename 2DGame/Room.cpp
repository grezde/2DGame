#include <fstream>
#include <iostream>
#include "Room.h"
#include "Game.h"

#include "RenderAction.h"
#include "InteractAction.h"
#include "TeleportAction.h"

Action* Room::getAction(char code, std::vector<std::string> data)
{
	if (code == 'i')
		return new RenderAction(data);
	if (code == 'a')
		return new InteractAction(data);
	if (code == 't')
		return new TeleportAction(data);

	return new Action(data);
}

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
		for (int j = 0; j < nrActions; j++) {
			ActionData a;
			std::string s;
			int nrLines;
			fin >> nrLines >> a.code;
			std::getline(fin, s);
			for (int k = 0; k < nrLines; k++) {
				std::getline(fin, s);
				a.text.push_back(s);
			}
			a.action = getAction(a.code, a.text);
			a.action->setRoom(this);
			types[typeNum].actions.push_back(a);
		}
	}
}

Room::Room(std::string name)
{
	roomName = name;
	roomPath = "files/rooms/" + name + "/";
	parseFile();

	for (int i = 0; i < rWidth * rHeight; i++)
		for (auto action : types[data[i]].actions)
			action.action->addLocation(i % rWidth, i / rWidth);

	tex.loadFromFile(roomPath + "image.png");
	spr.setTexture(tex);
	spr.setScale(SCALE, SCALE);
	spr.setPosition(0, 0);
}

Room::~Room()
{
	delete[] data;
}

void Room::setPlayer(Player* player)
{
	for (auto type : types)
		for (auto action : type.actions) {
			action.action->setPlayer(player);
			action.action->init();
		}
}

int Room::getUniqueAction(char code)
{
	int lookType = -1;
	for (int it = 0; it < types.size(); it++) {
		for (int ia = 0; ia < types[it].actions.size(); ia++)
			if (types[it].actions[ia].code == code) {
				lookType = it;
				break;
			}
		if (lookType != -1)
			break;
	}
	if (lookType == -1)
		return -1;

	for (int i = 0; i < rWidth * rHeight; i++)
		if (data[i] == lookType)
			return i;
	return -1;
}

bool Room::hasAction(char code, sf::Vector2i position)
{
	if (position.x < 0 || position.x >= rWidth)
		return false;
	if (position.y < 0 || position.y >= rHeight)
		return false;
	int type = data[position.y * rWidth + position.x];
	for (auto x : types[type].actions)
		if (x.code == code)
			return true;
	return false;
}

bool Room::positionValid(sf::Vector2f pos)
{
	if (pos.x < 0 || pos.x > rWidth)
		return false;
	if (pos.y < 0 || pos.y > rHeight)
		return false;

	int type = data[int(pos.y) * rWidth + int(pos.x)];
	return !types[type].solid;
}

sf::Vector2f Room::projectSpeed(sf::Vector2f oldPos, sf::Vector2f newPos)
{
	sf::Vector2f vel = newPos - oldPos;
	sf::Vector2i oldPosI(oldPos.x, oldPos.y);
	sf::Vector2i newPosI(newPos.x, newPos.y);

	if (newPos.x < 0 || newPos.x > rWidth)
		vel.x = 0;
	if (newPos.y < 0 || newPos.y > rHeight)
		vel.y = 0;
	if (newPos.x < 0 || newPos.x > rWidth || newPos.y < 0 || newPos.y > rHeight)
		return vel;

	int newType = data[newPosI.y * rWidth + newPosI.x];
	if (types[newType].solid == 1) {
		int typeX = data[oldPosI.y * rWidth + newPosI.x];
		int typeY = data[newPosI.y * rWidth + oldPosI.x];
		if (types[typeX].solid == 1)
			vel.x = 0;
		if (types[typeY].solid == 1)
			vel.y = 0;
	}

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
			if(action.action != nullptr)
				action.action->hlPointMoved();
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

void Room::drawBackground(sf::RenderWindow* window)
{
	window->draw(spr);
}

void Room::drawForeground(sf::RenderWindow* window)
{
	for (auto type : types)
		for (auto action : type.actions)
			action.action->draw(window);
}

void Room::update(float dt)
{
	for (auto type : types)
		for (auto action : type.actions)
			action.action->update(dt);
}