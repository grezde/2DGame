#include "SavePopupScene.h"
#include "Globals.h"

SavePopupScene::SavePopupScene(std::string name, SavePopupScene::SaveType type)
{
	spr.setTexture(*Globals::popupBoxTex);
	
	text2.setFont(*Globals::font);
	text2.setCharacterSize(25);
	text2.setPosition(20, 85);
	text2.setFillColor(sf::Color::Black);
	if(type == Saved)
		text2.setString("was saved.");
	if (type == Deleted)
		text2.setString("was deleted.");
	if (type == Loaded)
		text2.setString("was loaded.");
	highlighted.setFont(*Globals::font);
	highlighted.setCharacterSize(25);
	highlighted.setPosition(20, 35);
	highlighted.setFillColor(sf::Color(128, 0, 0));
	highlighted.setString(name);
}

void SavePopupScene::normalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spr, states);
	target.draw(highlighted, states);
	target.draw(text2, states);
}
