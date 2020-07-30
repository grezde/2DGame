#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	static sf::Texture* texture;
	static const int OFFSETS[4];

	sf::FloatRect position;
	bool selected;
	sf::Sprite left;
	sf::Sprite right;
	sf::Sprite center;
	sf::Text label;

private:
	void remake();

public:
	Button();
	Button(std::string text, sf::FloatRect position);

	void draw(sf::RenderWindow* window);

	void setSelected(bool selected);
	void setRect(sf::FloatRect position);
	void setText(std::string text);

};

