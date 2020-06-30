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
		for (int j = 0; j < nrActions; j++) {
			Action a;
			std::string s;
			int nrLines;
			fin >> nrLines >> a.code;
			std::getline(fin, s);
			for (int k = 0; k < nrLines; k++) {
				std::getline(fin, s);
				a.data.push_back(s);
			}
			types[typeNum].actions.push_back(a);
		}
	}
}

Room::Room(std::string name)
{
	roomPath = "files/rooms/" + name + "/";
	parseFile();

	tex.loadFromFile(roomPath + "image.png");
	spr.setTexture(tex);
	spr.setScale(SCALE, SCALE);
	spr.setPosition(0, 0);

	for(int it = 0; it < types.size(); it++)
		for (int ia = 0; ia < types[it].actions.size(); ia++)
			if (types[it].actions[ia].code == 'i') {// render image 
				sf::Texture* t = new sf::Texture();
				t->loadFromFile(roomPath + types[it].actions[ia].data[0]);
				textures.push_back(t);
				for(int i=0; i<rWidth*rHeight; i++)
					if (data[i] == it) {
						sf::Vector2f pos = sf::Vector2f(i % rWidth, i / rWidth + 1);
						sf::Sprite sp;
						sp.setTexture(*t);
						sp.setScale(SCALE, SCALE);
						sp.setOrigin(0, t->getSize().y);
						sprites.push_back(std::make_pair(sp, pos));
					}
			}
}

Room::~Room()
{
	delete[] data;
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

bool Room::positionValid(sf::Vector2f pos)
{
	if (pos.x < 0 || pos.x > rWidth)
		return false;
	if (pos.y < 0 || pos.y > rHeight)
		return false;

	int type = data[int(pos.y) * rWidth + int(pos.x)];
	return !types[type].solid;
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

	for (int i = 0; i < sprites.size(); i++)
		sprites[i].first.setPosition(getPosOnScreen(sprites[i].second));
}

sf::Vector2i Room::onEdges()
{
	float hw = Game::WIDTH / PIXPM;
	float hh = Game::HEIGHT / PIXPM;
	return sf::Vector2i(hlPoint.x <= hw || hlPoint.x >= rWidth - hw, hlPoint.y <= hh || hlPoint.y >= rHeight - hh);
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
	for (auto sp : sprites)
		window->draw(sp.first);
}
