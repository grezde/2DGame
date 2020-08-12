#include "ConditionAction.h"

#include <sstream>
#include <iostream>

#include "Globals.h"

ConditionAction::ConditionAction(std::vector<std::string> data)
	: Action(data)
{
	cp = ConditionParser::getParser(data[0]);
}

ConditionAction::~ConditionAction()
{
	for (Action* ac : actions)
		delete ac;
	delete cp;
}

void ConditionAction::setRoom(Room* roomPtr)
{
	room = roomPtr;
	for (Action* ac : actions)
		ac->setRoom(roomPtr);
}

void ConditionAction::setPlayer(Player* playerPtr)
{
	player = playerPtr;
	for (Action* ac : actions)
		ac->setPlayer(playerPtr);
}

void ConditionAction::addLocation(int x, int y)
{
	for (Action* ac : actions)
		ac->addLocation(x, y);
}

void ConditionAction::preinit()
{
	for (Action* ac : actions)
		ac->preinit();
}

void ConditionAction::init()
{
	for (Action* ac : actions)
		ac->init();
}

void ConditionAction::postinit()
{
	for (Action* ac : actions)
		ac->postinit();
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
	for (Action* ac : actions)
		ac->hlPointMoved();
}

void ConditionAction::reinitScene()
{
	for (Action* ac : actions)
		ac->reinitScene();
}

void ConditionAction::onKeyPress(sf::Keyboard::Key k)
{
	if(curent != nullptr)
		curent->onKeyPress(k);
}

void ConditionAction::onRead(std::istream& fin)
{
	for (int i = 0; i < cp->nChoices(); i++) {
		Action* a = Action::readFromStream(fin);
		actions.push_back(a);
	}
}

void ConditionAction::update(float dt)
{
	int i = cp->getChoice();
	if (i == -1)
		curent = nullptr;
	else
		curent = actions[i];

	if(curent != nullptr)
		curent->update(dt);
}
