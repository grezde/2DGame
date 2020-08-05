#include "SavePopupScene.h"
#include "Globals.h"

SavePopupScene::SavePopupScene(std::string name)
{
	spr.setTexture(*Globals::popupBoxTex);
	
	text2.setFont(*Globals::font);
	text2.setCharacterSize(30);
	text2.setPosition(20, 70);
	text2.setFillColor(sf::Color::Black);
	text2.setString("saved.");
	highlighted.setFont(*Globals::font);
	highlighted.setCharacterSize(30);
	highlighted.setPosition(20, 30);
	highlighted.setFillColor(sf::Color(128, 0, 0));
	highlighted.setString(name);
}

void SavePopupScene::normalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(spr, states);
	target.draw(highlighted, states);
	target.draw(text2, states);
}
