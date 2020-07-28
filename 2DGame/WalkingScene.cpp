#include "WalkingScene.h"
#include <fstream>
#include <iostream>

const float WalkingScene::SCALE = 5.0f;
WalkingScene* WalkingScene::curentWS = nullptr;

WalkingScene::WalkingScene(std::string roomName)
{
	r = new Room(roomName);
	p = new Player(r);
	r->setPlayer(p);
}

WalkingScene::~WalkingScene()
{
	delete p;
	delete r;
}

void WalkingScene::setNextScene(bool shouldExit, Scene* nextScene)
{
	curentWS->next = nextScene;
	curentWS->exit = shouldExit;
}

void WalkingScene::draw(sf::RenderWindow* window)
{
	r->drawBackground(window);
	p->draw(window);
	r->drawForeground(window);
}

void WalkingScene::update(float dt)
{
	r->update(dt);
	p->update(dt);
}