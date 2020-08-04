#pragma once
#include "Scene.h"

class InventoryScene :
	public Scene
{
private:
	sf::Texture backtex;
	sf::Sprite backspr;
	std::vector<sf::Text> labels;
	std::vector<sf::Text> decoration;
	sf::Text description;
	std::vector<sf::Text> stats;
	int selected = 0;
	int usageSelected = -1;

public:
	static const sf::Color SELECTED;
	static const sf::Color UNSELECTED;

private:
	sf::Text createLabel(bool big);
	void setSelected(int newsel);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	InventoryScene();

	virtual void update(float dt) override;
	virtual void onKeyPress(sf::Keyboard::Key key) override;
	virtual void onMousePress(sf::Event::MouseButtonEvent mev) override;
};

