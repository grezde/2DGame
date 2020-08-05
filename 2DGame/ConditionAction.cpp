#include "ConditionAction.h"

#include <sstream>
#include <iostream>

#include "Globals.h"

ConditionAction::ConditionAction(std::vector<std::string> data)
	: Action(data)
{
	varname = data[0];
}

ConditionAction::~ConditionAction()
{
	for (auto pair : actions)
		delete pair.second;
}

void ConditionAction::setRoom(Room* roomPtr)
{
	room = roomPtr;
	for (auto pair : actions)
		pair.second->setRoom(roomPtr);
}

void ConditionAction::setPlayer(Player* playerPtr)
{
	player = playerPtr;
	for (auto pair : actions)
		pair.second->setPlayer(playerPtr);
}

void ConditionAction::addLocation(int x, int y)
{
	for (auto p : actions)
		p.second->addLocation(x, y);
}

void ConditionAction::preinit()
{
	for (auto p : actions)
		p.second->preinit();
}

void ConditionAction::init()
{
	for (auto p : actions)
		p.second->init();
}

void ConditionAction::postinit()
{
	for (auto p : actions)
		p.second->postinit();
}

void ConditionAction::drawBackground(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (curent != nullptr)
		curent->drawBackground(target, states);
}

void ConditionAction::drawForeground(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (curent != nullptr)
		curent->drawForeground(target, states);
}

void ConditionAction::trigger()
{
	if (curent != nullptr)
		curent->trigger();
}


void ConditionAction::hlPointMoved()
{
	for (auto p : actions)
		p.second->hlPointMoved();
}

void ConditionAction::reinitScene()
{
	for (auto p : actions)
		p.second->reinitScene();
}

void ConditionAction::onKeyPress(sf::Keyboard::Key k)
{
	if(curent != nullptr)
		curent->onKeyPress(k);
}

void ConditionAction::onRead(std::istream& fin)
{
	std::istringstream iss(data[1]+" ");
	char c;
	std::string s;
	while (!iss.eof()) {
		int x;
		iss >> x;
		iss.get(c);
		if (iss.eof())
			break;
		if (c == '-')
			x = -(3 * Save::MAXINT + x);
		else if (c == '+')
			x = 3 * Save::MAXINT + x;
		Action* a = Action::readFromStream(fin);
		;;;
		actions[x] = a;
	}
	update(0);
}

void ConditionAction::update(float dt)
{
	int val = Globals::save->geti(varname);
	if (val != curentindex) {
		curentindex = val;
		for (auto pair : actions) {
			if (pair.first < -2 * Save::MAXINT) {
				int realx = - pair.first - 3*Save::MAXINT;
				if (val <= realx) {
					curent = pair.second;
					return;
				}
			} 
			else if (pair.first > 2 * Save::MAXINT) {
				int realx = pair.first - 3 * Save::MAXINT;
				if (val >= realx) {
					curent = pair.second;
					return;
				}
			}
			else if (pair.first == val) {
				curent = pair.second;
				return;
			}
		}
		curent = nullptr;
	}

	if(curent != nullptr)
		curent->update(dt);
}
