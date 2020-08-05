#include "InventoryScene.h"
#include "Inventory.h"
#include <iostream>

const sf::Color InventoryScene::SELECTED = sf::Color(200, 0, 0);
const sf::Color InventoryScene::UNSELECTED = sf::Color(0, 0, 0);

sf::Text InventoryScene::createLabel(bool big)
{
	sf::Text t;
	t.setFont(*Globals::font);
	if (big)
		t.setCharacterSize(26);
	else
		t.setCharacterSize(20);
	t.setFillColor(UNSELECTED);
	t.setLineSpacing(1.2f);
	return t;
}

void InventoryScene::setSelected(int newsel)
{
	if (newsel < 0 || newsel >= Inventory::SLOTS)
		return;
	labels[selected].setFillColor(UNSELECTED);
	labels[newsel].setFillColor(SELECTED);
	selected = newsel;
	Item* it = Inventory::getItemAt(selected);
	stats.clear();
	if (it == nullptr) 
		description.setString("");
	else 
		description.setString(it->info);
	float start = description.getGlobalBounds().top + description.getGlobalBounds().height;
	std::vector<std::string> statStrs = Inventory::getFormatedStats(selected);
	for (int i = 0; i < statStrs.size(); i++) {
		stats.push_back(createLabel(false));
		stats[i].setString(statStrs[i]);
		stats[i].setPosition(400, start+30+35*i);
	}
}

void InventoryScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backspr, states);
	target.draw(description, states);
	for (int i = 0; i < labels.size(); i++)
		if (labels[i].getString()[4] != '-' || i == selected)
			target.draw(labels[i], states);
	for (const sf::Text& label : decoration)
		target.draw(label, states);
	for (const sf::Text& label : stats)
		target.draw(label, states);
}

InventoryScene::InventoryScene()
{
	backtex.loadFromFile("Files/items/menu.png");
	backspr.setTexture(backtex);
	std::vector<std::string> strings = Inventory::getFormatedInventory();
	for (int i = 0; i < strings.size(); i++) {
		labels.push_back(createLabel(false));
		labels[i].setPosition(120, 140 + 40 * i);
		labels[i].setString(strings[i]);
	}
	description = createLabel(false);
	description.setPosition(400, 265);
	setSelected(0);
}

void InventoryScene::update(float dt)
{

}

void InventoryScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
		setSelected(selected - 1);
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
		setSelected(selected + 1);
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