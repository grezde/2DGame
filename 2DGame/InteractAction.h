#pragma once
#include "Action.h"

class InteractAction : public Action
{
private:
	std::vector<sf::Vector2i> positions;

public:
	InteractAction(std::vector<std::string> data) : Action(data) {};

	virtual void addLocation(int x, int y) override;
	virtual void update(float dt) override;
	virtual void trigger() override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;

};

