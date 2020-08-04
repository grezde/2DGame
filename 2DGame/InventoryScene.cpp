#include "InventoryScene.h"
#include "Inventory.h"
#include <iostream>

const sf::Color InventoryScene::SELECTED = sf::Color(200, 0, 0);
const sf::Color InventoryScene::UNSELECTED = sf::Color(0, 0, 0);

sf::Text InventoryScene::getLabel(bool big)
{
	sf::Text t;
	t.setFont(*Globals::font);
	if (big)
		t.setCharacterSize(26);
	else
		t.setCharacterSize(20);
	t.setFillColor(UNSELECTED);
	return t;
}

InventoryScene::InventoryScene()
{
	temp.setFillColor(sf::Color::White);
	temp.setSize({ 600, 480 });
	temp.setPosition({ 100, 60 });
	inside.setSize({ 175, 175 });
	inside.setPosition({ 100 + 600 - 190, 75 });
	inside.setFillColor(sf::Color::Black);
	std::vector<std::string> strings = Inventory::getFormatedInventory();
	for (int i = 0; i < strings.size(); i++) {
		labels.push_back(getLabel(false));
		labels[i].setPosition(120, 140 + 40 * i);
		labels[i].setString(strings[i]);
	}
	labels[0].setFillColor(SELECTED);
	for (int i = 0; i < 2; i++)
		decoration.push_back(getLabel(true));
	decoration[0].setString("Inventar");
	decoration[0].setPosition(120, 80);
	decoration[1].setString("Stats");
	decoration[1].setPosition(400, 80);
}

void InventoryScene::draw(sf::RenderWindow* window)
{
	window->draw(temp);
	window->draw(outline);
	window->draw(inside);
	for (sf::Text& label : labels)
		window->draw(label);
	for (sf::Text& label : decoration)
		window->draw(label);
}

void InventoryScene::update(float dt)
{

}

void InventoryScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
		if (selected == 0)
			return;
		labels[selected].setFillColor(UNSELECTED);
		labels[selected - 1].setFillColor(SELECTED);
		selected--;
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
		if (selected == Inventory::SLOTS - 1)
			return;
		labels[selected].setFillColor(UNSELECTED);
		labels[selected + 1].setFillColor(SELECTED);
		selected++;
	}
	else if (key == sf::Keyboard::Z || key == sf::Keyboard::Enter) {
		if(usageSelected == -1)
			usageSelected = 0;
	}
	else if (key == sf::Keyboard::Escape) {
		exit = true;
		next = nullptr;
	}
}

void InventoryScene::onMousePress(sf::Event::MouseButtonEvent mev)
{
	std::cout << mev.x << " " << mev.y << "\n";
}
