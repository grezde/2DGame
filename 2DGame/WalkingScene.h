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

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	WalkingScene(std::string roomName);
	~WalkingScene();

	static void setNextScene(bool shouldExit, Scene* nextScene);

	virtual void update(float dt) override;
	virtual void reinit() override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;
};

