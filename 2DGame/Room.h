#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Action.h"

class Player;

class Room
{
public:
	struct ActionData {
		char code;
		Action* action;
		std::vector<std::string> text;
	};

	static struct Type {
		int solid;
		std::vector<ActionData> actions;
	};

	static const float SCALE;
	static const float PIXPM;

private:
	std::string roomPath;
	std::string roomName;

	int rWidth, rHeight;
	int* data;
	std::vector<Type> types;

	sf::Texture tex;
	sf::Sprite spr;

	sf::Vector2f hlPoint;

private:
	void parseFile();
	
	Action* getAction(char code, std::vector<std::string> data);

public:
	Room(std::string path);
	~Room();

	void setPlayer(Player* player);

	int getUniqueAction(char code);
	bool hasAction(char code, sf::Vector2i position);

	bool positionValid(sf::Vector2f pos);
	sf::Vector2f projectSpeed(sf::Vector2f oldPos, sf::Vector2f newPos);

	void setCenterPosition(sf::Vector2f pos);
	sf::Vector2f getPosOnScreen(sf::Vector2f pos);

	void drawBackground(sf::RenderWindow* window);
	void drawForeground(sf::RenderWindow* window);
	void update(float dt);

	inline int width()  { return rWidth;  };
	inline int height() { return rHeight; };
	inline std::string filepath() { return roomPath; }
	inline std::string name() { return roomName; }

};

