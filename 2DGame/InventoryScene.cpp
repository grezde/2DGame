#include "InventoryScene.h"
#include "Inventory.h"
#include <iostream>

sf::Text InventoryScene::createLabel(bool big)
{
	sf::Text t;
	t.setFont(*Globals::font);
	if (big)
		t.setCharacterSize(26);
	else
		t.setCharacterSize(20);
	t.setFillColor(sf::Color::Black);
	t.setLineSpacing(1.2f);
	return t;
}

void InventoryScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backspr, states);
	target.draw(description, states);
	target.draw(ts, states);
	for (const sf::Text& label : decoration)
		target.draw(label, states);
	for (const sf::Text& label : stats)
		target.draw(label, states);
}

InventoryScene::InventoryScene()
	: ts(this)
{
	backtex.loadFromFile("Files/items/menu.png");
	backspr.setTexture(backtex);
	ts.setStrings(Inventory::getFormatedInventory());
	ts.setPosition(sf::Vector2f(120, 140));
	description = createLabel(false);
	description.setPosition(400, 265);
	ts.setSelected(0);
}

void InventoryScene::update(float dt)
{
}

void InventoryScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape) {
		exit = true;
		next = nullptr;
	}
	else
		ts.onKeyPress(key);
}

void InventoryTS::onSelected(int newsel)
{
	Item* it = Inventory::getItemAt(newsel);
	parent->stats.clear();
	if (it == nullptr)
		parent->description.setString("");
	else
		parent->description.setString(it->info);
	float start = parent->description.getGlobalBounds().top + parent->description.getGlobalBounds().height;
	std::vector<std::string> statStrs = Inventory::getFormatedStats(newsel);
	for (int i = 0; i < statStrs.size(); i++) {
		parent->stats.push_back(parent->createLabel(false));
		parent->stats[i].setString(statStrs[i]);
		parent->stats[i].setPosition(400, start + 30 + 35 * i);
	}
}

InventoryTS::InventoryTS(InventoryScene* parent)
	: parent(parent), TextSelector(20, 2)
{
}

void InventoryTS::finishedSelection(int sel)
{
	std::cout << "USE " << sel << "\n";
}
