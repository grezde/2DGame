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

void ConditionAction::onRead(std::ifstream& fin)
{
	std::istringstream iss(data[1]+" ");
	char c;
	while (!iss.eof()) {
		int x;
		iss >> x;
		iss.get(c);
		if (c == '-')
			x = -(3 * Save::MAXINT + x);
		else if (c == '+')
			x = 3 * Save::MAXINT + x;
		Action* a = Action::readFromFile(fin);
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
				int realx = -pair.first - 3*Save::MAXINT;
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

	if(curent)
		curent->update(dt);
}
