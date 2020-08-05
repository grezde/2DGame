#include "ButtonSet.h"
#include <iostream>

const float ButtonSet::PRESS_INTERVAL = 1.0f;

void ButtonSet::select(int index)
{
	if(selindex != -1)
		buttons[selindex].setSelected(false);
	if(index != -1)
		buttons[index].setSelected(true);
	selindex = index;
}

ButtonSet::ButtonSet(std::vector<std::string> options, sf::FloatRect bounds, float btnSpace)
{
	buttonSpace = btnSpace;
	float btnh = bounds.height / float(options.size() + (options.size()-1) * buttonSpace);
	for (int i = 0; i < options.size(); i++) {
		sf::FloatRect btnb(bounds.left, bounds.top + (1+buttonSpace) * i * btnh, bounds.width, btnh);
		buttons.push_back(Button(options[i], btnb));
	}
	buttons[0].setSelected(true);
	selindex = 0;
}

void ButtonSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Button& b : buttons)
		target.draw(b, states);
}

void ButtonSet::moveSelection(int di)
{
	int secindex = selindex + di;
	while (secindex >= 0 && secindex <= buttons.size() - 1 && !buttons[secindex].isEnabled())
		secindex += di;
	if (secindex >= 0 && secindex <= buttons.size() - 1) {
		buttons[selindex].setSelected(false);
		buttons[secindex].setSelected(true);
		selindex = secindex;
	}
}

void ButtonSet::onKeyPress(sf::Keyboard::Key key)
{
	if (selindex == -1)
		return;

	if(key == sf::Keyboard::Z || key == sf::Keyboard::Enter)
		finsihedSelection(selindex);

	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
		moveSelection(-1);

	if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
		moveSelection(1);
}
