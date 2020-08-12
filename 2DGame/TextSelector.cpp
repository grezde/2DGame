#include "TextSelector.h"
#include "Globals.h"

const sf::Color TextSelector::SELECTED = sf::Color(180, 0, 0);
const sf::Color TextSelector::UNSELECTED = sf::Color(0, 0, 0);

void TextSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < labels.size(); i++)
		if (labels[i].getString()[4] != '-' || i == selected)
			target.draw(labels[i], states);
}

void TextSelector::setSelected(int newsel)
{
	if (newsel < 0 || newsel >= labels.size())
		return;
	labels[selected].setFillColor(UNSELECTED);
	labels[newsel].setFillColor(SELECTED);
	onSelected(newsel);
	selected = newsel;
}

TextSelector::TextSelector(float charSize, float lineSpacing)
{
	charsize = charSize;
	linesp = lineSpacing;
	selected = 0;
}

void TextSelector::setStrings(std::vector<std::string> values)
{
	if (values.empty())
		return;

	labels.clear();
	selected = 0;
	for (std::string s : values) {
		labels.push_back(sf::Text());
		labels.back().setCharacterSize(charsize);
		labels.back().setFont(*Globals::font);
		labels.back().setString(s);
		labels.back().setFillColor(UNSELECTED);
	}
	labels[0].setFillColor(SELECTED);
}

void TextSelector::setPosition(sf::Vector2f pos)
{
	for (int i = 0; i < labels.size(); i++)
		labels[i].setPosition(pos + sf::Vector2f(0, linesp * charsize * i));
}

sf::Vector2f TextSelector::getSize()
{
	float width = 0;
	for (sf::Text& t : labels)
		width = std::max(t.getGlobalBounds().width, width);
	return sf::Vector2f(width, linesp * charsize * (labels.size() - 1) + charsize);
}

void TextSelector::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
		setSelected(selected - 1);
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
		setSelected(selected + 1);
	}
	else if (key == sf::Keyboard::Z || key == sf::Keyboard::Enter) {
		finishedSelection(selected);
	}
}
