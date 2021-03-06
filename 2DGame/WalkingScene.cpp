#include "WalkingScene.h"
#include <fstream>
#include "InventoryScene.h"
#include "PauseMenuScene.h"
#include "Globals.h"

const float WalkingScene::SCALE = 5.0f;
WalkingScene* WalkingScene::curentWS = nullptr;

void WalkingScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	r->drawBackground(target, states);
	target.draw(*p, states);
	r->drawForeground(target, states);
}

WalkingScene::WalkingScene(std::string roomName)
{
	saveDraw = true;
	Globals::save->sets("current_room", roomName);
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

void WalkingScene::update(float dt)
{
	p->preupdate(dt);
	r->update(dt);
	p->update(dt);
}

void WalkingScene::reinit()
{
	r->reinitScene();
}

void WalkingScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::C) {
		next = new InventoryScene();
	}
	else if (key == sf::Keyboard::Escape) {
		next = new PauseMenuScene();
	}
	else
		r->onKeyPress(key);
}

void WalkingScene::onLostFocus()
{
	this->next = new PauseMenuScene();
}
