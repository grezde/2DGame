#pragma once
#include "Scene.h"

class InventoryScene :
	public Scene
{
private:
	sf::Texture backtex;
	sf::Sprite backspr;
	sf::RectangleShape temp, outline, inside;
	std::vector<sf::Text> labels;
	std::vector<sf::Text> decoration;

	int selected = 0;
	int usageSelected = -1;

public:
	static const sf::Color SELECTED;
	static const sf::Color UNSELECTED;

private:
	sf::Text getLabel(bool big);

public:
	InventoryScene();

	virtual void draw(sf::RenderWindow* window) override;
	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;
	virtual void onMousePress(sf::Event::MouseButtonEvent mev) override;
};

