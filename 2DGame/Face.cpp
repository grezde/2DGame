#include "Face.h"

const float Face::INTERVAL = 0.1f;

void Face::setDrawing(int i)
{
	spr.setTextureRect(sf::IntRect(tex.getSize().x / 2 * i, 0, tex.getSize().x / 2, tex.getSize().y));
}

Face::Face(std::string name)
{
	tex.loadFromFile("Files/characters/" + name + "_face.png");
	spr.setTexture(tex);
	spr.setOrigin(tex.getSize().x/4, tex.getSize().x/2);
	setDrawing(0);
}

void Face::setPosition(float x, float y)
{
	spr.setPosition(x, y);
}

void Face::setScale(float s)
{
	spr.setScale(s, s);
}

void Face::setActive(bool a)
{
	if (a == active)
		return;
	if (a == false) {
		setDrawing(0);
		i = 0;
		time = 0;
	}
	active = a;
}

void Face::update(float dt)
{
	if (!active)
		return;
	time += dt;
	if (time > INTERVAL) {
		time -= INTERVAL;
		i++;
		if (i == 2)
			i = 0;
		setDrawing(i);
	}
}

void Face::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spr, states);
}
