#include "Room.h"
#include <fstream>

const float Room::SCALE = 5.0f;
const float Room::PIXPM = 16;

Room::Room(std::string name)
{
	roomPath = "files/rooms/" + name + "/";

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

	roomTex.loadFromFile(roomPath + "image.png");
	roomSprite.setTexture(roomTex);
	roomSprite.setScale(SCALE, SCALE);
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

void Room::draw(sf::RenderWindow* window)
{
	window->draw(roomSprite);
}

void Room::update(float dt)
{
}
