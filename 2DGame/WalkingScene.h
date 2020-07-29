#pragma once
#include "Scene.h"
#include <string>
#include "Player.h"
#include "Room.h"

class WalkingScene : public Scene
{
public:
	static const float SCALE;

private:
	static WalkingScene* curentWS;
	Player* p;
	Room* r;

public:
	WalkingScene(std::string roomName);
	~WalkingScene();

	static void setNextScene(bool shouldExit, Scene* nextScene);
	virtual void draw(sf::RenderWindow* window);
	virtual void update(float dt);
	virtual void reinit();
};

