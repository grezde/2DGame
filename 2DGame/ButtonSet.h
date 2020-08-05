#pragma once
#include "GameElement.h"
#include "Button.h"

class ButtonSet : public IKeyListener
{
private:
	static const float PRESS_INTERVAL;
	float sincePress = 0.0f;
	int selindex;

protected:
	float buttonSpace = 0.5f;
	std::vector<Button> buttons;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void moveSelection(int di);

protected:
	inline int selectedIndex() { return selindex; }
	void select(int index);

public:
	ButtonSet(std::vector<std::string> options, sf::FloatRect bounds);

	void onKeyPress(sf::Keyboard::Key key);
	virtual void finsihedSelection(int selected) = 0;
};