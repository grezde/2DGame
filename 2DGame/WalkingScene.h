#pragma once
#include "Scene.h"
#include <string>

class WalkingScene : public Scene
{
public:
	float SCALE = 5;
	float PLAYER_SCALE = 5;

private:
	
	struct Action {
		char code;
		std::vector<std::string> data;
	};

	static struct Type {
		bool solid;
		std::vector<Action> actions;
	};

	int width, height;
	int* data;
	std::vector<Type> types;
	
	sf::Texture roomTex;
	sf::Sprite roomSprite;

	sf::Texture playerTex;
	sf::Sprite playerSprite;

	float timeSinceStopped;

private:
	void parseFile(std::string roomPath);
	
	void setPlayerTex(int i, int j);

public:
	WalkingScene(std::string roomName);
	~WalkingScene();

	virtual void draw(sf::RenderWindow* window);
	virtual void update(float dt);
};

