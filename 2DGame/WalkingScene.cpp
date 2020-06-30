#include "WalkingScene.h"
#include <fstream>
#include <iostream>

void WalkingScene::parseFile(std::string roomPath)
{
	std::ifstream fin(roomPath + "format.txt");
	fin >> height >> width;

	data = new int[width * height];
	int maxtype = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			fin >> data[i * width + j];
			if (data[i * width + j] > maxtype)
				maxtype = data[i * width + j];
		}

	types = std::vector<Type>(maxtype + 1);
	for (int i = 0; i <= maxtype; i++) {
		int typeNum, nrActions;
		fin >> typeNum;
		std::cout << typeNum << " ";
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

void WalkingScene::setPlayerTex(int i, int j)
{
	sf::IntRect rect;
	rect.left = j * playerTex.getSize().x / 4;
	rect.top = i * playerTex.getSize().y / 4;
	rect.height = playerTex.getSize().y / 4;
	rect.width = playerTex.getSize().x / 4;
	playerSprite.setTextureRect(rect);
}

WalkingScene::WalkingScene(std::string roomName)
{
	std::string roomPath = "Files/rooms/" + roomName + "/";
	parseFile(roomPath);

	roomTex.loadFromFile(roomPath + "image.png");
	roomSprite.setTexture(roomTex);
	roomSprite.setScale(SCALE, SCALE);

	std::cout << "Harta (" << height << "m, " << width << "m)\n";
	std::cout << "Harta (" << roomTex.getSize().y << "px, " << roomTex.getSize().y << "px)\n";
	std::cout << "Cantitatea px/m: " << roomTex.getSize().y / height << "\n";

	playerTex.loadFromFile("Files/global_pictures/player.png");
	playerSprite.setTexture(playerTex);
	playerSprite.setScale(SCALE, SCALE);
	playerSprite.setOrigin(playerTex.getSize().x / 8, playerTex.getSize().y / 4);
	playerSprite.setPosition(400, 400);
	setPlayerTex(0, 0);

	std::cout << "Player (" << playerTex.getSize().y << "px, " << playerTex.getSize().y << "px)\n";
}

WalkingScene::~WalkingScene()
{
	delete[] data;
}

void WalkingScene::draw(sf::RenderWindow* window)
{
	window->draw(roomSprite);
	window->draw(playerSprite);
}

void WalkingScene::update(float dt)
{
	float dx=0, dy=0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dx -= 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dx += 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		dy -= 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dy += 1.0f;
	
	if (dx == 1.0f)
		setPlayerTex(1, 0);
	if (dx == -1.0f)
		setPlayerTex(3, 0);
	if (dy == 1.0f)
		setPlayerTex(0, 0);
	if (dy == -1.0f)
		setPlayerTex(2, 0);

	if (dx != 0 && dy != 0) {
		dx *= 0.7f;
		dy *= 0.7f;
	}

	playerSprite.move(dx * dt * 48 * SCALE, dy * dt * 48 * SCALE);
}
