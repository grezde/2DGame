#include "Button.h"
#include "Globals.h"

sf::Texture* Button::texture = nullptr;
const int Button::OFFSETS[4] = { 7, 5, 3, 9 };

void Button::remake()
{
	int offin = 2 * int(selected);
	sf::Vector2u texsize = texture->getSize();
	left.setTextureRect(sf::IntRect(
		0, texsize.y / 2 * selected,
		OFFSETS[offin], texsize.y / 2
	));
	right.setTextureRect(sf::IntRect(
		texsize.x - OFFSETS[offin + 1],
		texsize.y / 2 * selected,
		OFFSETS[offin + 1], texsize.y / 2
	));
	center.setTextureRect(sf::IntRect(
		OFFSETS[offin], texsize.y / 2 * selected,
		texsize.x - OFFSETS[offin + 1] - OFFSETS[offin],
		texsize.y / 2
	));
	float yscale = position.height / float(texsize.y / 2);
	float xscale = (position.width - float(OFFSETS[offin] + OFFSETS[offin + 1]) * yscale)
		/ (texsize.x - OFFSETS[offin + 1] - OFFSETS[offin]);
	left.setScale(yscale, yscale);
	right.setScale(yscale, yscale);
	center.setScale(xscale, yscale);
	left.setPosition(position.left, position.top);
	right.setPosition(position.left + position.width - float(OFFSETS[offin + 1]) * yscale, position.top);
	center.setPosition(position.left + float(OFFSETS[offin]) * yscale, position.top);

	label.setCharacterSize(textPercent * position.height);
	sf::FloatRect labelb = label.getGlobalBounds();
	sf::FloatRect centerb = center.getGlobalBounds();
	label.setPosition(
		centerb.left + (centerb.width - labelb.width) / 2,
		centerb.top + (centerb.height - labelb.height) / 2 + paddingTop
	);
}

Button::Button()
{
	if (texture == nullptr) {
		texture = new sf::Texture();
		texture->loadFromFile("Files/global/buttons.png");
	}
	label.setFillColor(sf::Color::Black);
	label.setFont(*Globals::font);
	left.setTexture(*texture);
	center.setTexture(*texture);
	right.setTexture(*texture);
	enabled = true;
}

Button::Button(std::string text, sf::FloatRect position)
	: Button()
{
	selected = false;
	label.setString(text);
	this->position = position;
	remake();
}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(center);
	window->draw(left);
	window->draw(right);
	window->draw(label);
}

void Button::setSelected(bool selected)
{
	if (this->selected == selected)
		return;

	this->selected = selected;
	remake();
}

void Button::setEnabled(bool enabled)
{
	this->enabled = enabled;
	if (enabled)
		label.setFillColor(sf::Color::Black);
	else
		label.setFillColor(sf::Color(120, 120, 120));
}

void Button::setRect(sf::FloatRect position)
{
	this->position = position;
	remake();
}

void Button::setText(std::string text)
{
	label.setCharacterSize(0);
	label.setString(text);
	remake();
}

void Button::setPaddingTop(float pt)
{
	paddingTop = pt;
	remake();
}
