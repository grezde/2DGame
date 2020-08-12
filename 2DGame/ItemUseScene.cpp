#include "ItemUseScene.h"
#include "Inventory.h"
#include "Game.h"

ItemUseTS::ItemUseTS(ItemUseScene* parent)
	: parent(parent), TextSelector(25, 1.8f)
{
}

void ItemUseTS::onSelected(int newsel)
{
}

void ItemUseTS::finishedSelection(int sel)
{
	if (sel == nChoices() - 1)
		parent->exit = true;
	else if (sel == nChoices() - 2) {
		Inventory::removeInventory(parent->invIndex);
		parent->exit = true;
	}
	else {
		Inventory::getItemAt(parent->invIndex)->type->useItem(parent->invIndex, sel);
		parent->exit = true;
	}
}

ItemUseScene::ItemUseScene(int invIndex)
	: ts(this)
{
	this->invIndex = invIndex;
	std::vector<std::string> values = Inventory::getItemAt(invIndex)->type->useNames;
	values.push_back("Arunca");
	values.push_back("Cancel");
	ts.setStrings(values);
	sf::Vector2f size = ts.getSize();
	sf::Vector2f position((Game::WIDTH - size.x)/2, (Game::HEIGHT - size.y) / 2);
	ts.setPosition(position);
	rint.setPosition(position - sf::Vector2f(15, 15));
	rint.setSize(size + sf::Vector2f(30, 30));
	rint.setFillColor(sf::Color::White);
	rext.setPosition(rint.getPosition() - sf::Vector2f(3, 3));
	rext.setSize(rint.getSize() + sf::Vector2f(6, 6));
	rext.setFillColor(sf::Color::Black);
}

void ItemUseScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rext, states);
	target.draw(rint, states);
	target.draw(ts, states);
}

void ItemUseScene::update(float dt)
{
}

void ItemUseScene::onKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
		exit = true;
	else
		ts.onKeyPress(key);
}
