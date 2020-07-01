#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Room
{
public:
	struct Action {
		char code;
		std::vector<std::string> data;
	};

	static struct Type {
		int solid;
		std::vector<Action> actions;
	};

	static const float SCALE;
	static const float PIXPM;

private:
	std::string roomPath;

	int rWidth, rHeight;
	int* data;
	std::vector<Type> types;

	std::vector<sf::Texture*> textures;
	std::vector<std::pair<sf::Sprite, sf::Vector2f>> sprites;

	sf::Texture tex;
	sf::Sprite spr;

	sf::Vector2f hlPoint;

private:
	void parseFile();

public:
	Room(std::string path);
	~Room();

	int getUniqueAction(char code);
	bool positionValid(sf::Vector2f pos);
	sf::Vector2f projectSpeed(sf::Vector2f oldPos, sf::Vector2f newPos);

	void setCenterPosition(sf::Vector2f pos);
	sf::Vector2i onEdges();
	sf::Vector2f getPosOnScreen(sf::Vector2f pos);

	void drawBackground(sf::RenderWindow* window);
	void drawForeground(sf::RenderWindow* window);

	inline int width()  { return rWidth;  };
	inline int height() { return rHeight; };

};

