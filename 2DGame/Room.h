#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class Room : public IGameElement
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

	sf::Texture roomTex;
	sf::Sprite roomSprite;

public:
	Room(std::string path);
	~Room();

	int getUniqueAction(char code);

	virtual void draw(sf::RenderWindow* window);
	virtual void update(float dt);

	inline int width()  { return rWidth;  };
	inline int height() { return rHeight; };

};

