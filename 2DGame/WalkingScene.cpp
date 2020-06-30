#include "WalkingScene.h"
#include <fstream>
#include <iostream>

const float WalkingScene::SCALE = 5.0f;

WalkingScene::WalkingScene(std::string roomName)
{
	r = new Room(roomName);
	int spos = r->getUniqueAction('s');
	p = new Player(sf::Vector2i(spos%r->width(), spos/r->width()), r);
}

WalkingScene::~WalkingScene()
{
	delete p;
	delete r;
}

void WalkingScene::draw(sf::RenderWindow* window)
{
	r->draw(window);
	p->draw(window);
}

void WalkingScene::update(float dt)
{
	p->update(dt);
}
