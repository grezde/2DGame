#pragma once
#include "Scene.h"
#include "Button.h"

class ButtonSet : public IGameElement
{
private:
	
	static const float PRESS_INTERVAL;
	float sincePress;
	int selindex;

protected:
	float buttonSpace = 0.5f;
	std::vector<Button> buttons;
	inline int selectedIndex() { return selindex; }
	void select(int index);

public:
	ButtonSet(std::vector<std::string> options, sf::FloatRect bounds);

	virtual void finsihedSelection(int selected) = 0;
	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
};