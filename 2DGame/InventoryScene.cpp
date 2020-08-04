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

InventoryScene::InventoryScene()
{
	temp.setFillColor(sf::Color::White);
	temp.setSize({ 600, 480 });
	temp.setPosition({ 100, 60 });
	outline.setSize({ 75, 75 });
	outline.setPosition({ 425, 175 });
	outline.setFillColor(sf::Color::Black);
	inside.setSize({ 175, 175 });
	inside.setPosition({ 100 + 600 - 190, 75 });
	inside.setFillColor(sf::Color::Black);
	std::vector<std::string> strings = Inventory::getFormatedInventory();
	for (int i = 0; i < strings.size(); i++) {
		labels.push_back(createLabel(false));
		labels[i].setPosition(120, 140 + 40 * i);
		labels[i].setString(strings[i]);
	}
	labels[0].setFillColor(SELECTED);
	for (int i = 0; i < 3; i++)
		decoration.push_back(createLabel(i < 2));
	decoration[0].setString("Inventar");
	decoration[0].setPosition(120, 80);
	decoration[1].setString("Stats");
	decoration[1].setPosition(400, 80);
	decoration[2].setPosition(425, 145);
	decoration[2].setString("Type");
	description = createLabel(false);
	description.setPosition(400, 265);
	setSelected(0);
}

void InventoryScene::draw(sf::RenderWindow* window)
{
	window->draw(temp);
	window->draw(outline);
	window->draw(inside);
	window->draw(description);
	for (int i = 0; i < labels.size(); i++)
		if(labels[i].getString()[4] != '-' || i == selected)
			window->draw(labels[i]);
	for (sf::Text& label : decoration)
		window->draw(label);
	for (sf::Text& label : stats)
		window->draw(label);
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

void InventoryScene::onMousePress(sf::Event::MouseButtonEvent mev)
{
	std::cout << mev.x << " " << mev.y << "\n";
}
