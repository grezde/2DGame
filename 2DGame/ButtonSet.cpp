#include "ButtonSet.h"
#include <iostream>

const float ButtonSet::PRESS_INTERVAL = 1.0f;
float ButtonSet::sincePress = 2.0f;

void ButtonSet::select(int index)
{
	if(selindex != -1)
		buttons[selindex].setSelected(false);
	if(index != -1)
		buttons[index].setSelected(true);
	selindex = index;
}

ButtonSet::ButtonSet(std::vector<std::string> options, sf::FloatRect bounds)
{
	float btnh = bounds.height / float(options.size() + (options.size()-1) * buttonSpace);
	for (int i = 0; i < options.size(); i++) {
		sf::FloatRect btnb(bounds.left, bounds.top + (1+buttonSpace) * i * btnh, bounds.width, btnh);
		buttons.push_back(Button(options[i], btnb));
	}
	buttons[0].setSelected(true);
	selindex = 0;
}

void ButtonSet::draw(sf::RenderWindow* window)
{
}

void ButtonSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Button& b : buttons)
		target.draw(b, states);
}

void ButtonSet::update(float dt)
{
	if (selindex == -1)
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		finsihedSelection(selindex);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		int secindex = selindex-1;
		while (secindex >= 0 && !buttons[secindex].isEnabled())
			secindex--;
		if (secindex >= 0 && sincePress > PRESS_INTERVAL) {
			buttons[selindex].setSelected(false);
			buttons[selindex - 1].setSelected(true);
			selindex--;
		}
		sincePress = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		int secindex = selindex + 1;
		while (secindex <= buttons.size()-1 && !buttons[secindex].isEnabled())
			secindex++;
		if (sincePress > PRESS_INTERVAL && secindex <= buttons.size() - 1) {
			buttons[selindex].setSelected(false);
			buttons[selindex + 1].setSelected(true);
			selindex++;
		}
		sincePress = 0;
	}
	else
		sincePress = PRESS_INTERVAL;
	sincePress += dt;
}
