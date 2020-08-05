#include "Game.h"
#include "WalkingScene.h"
#include "MenuScene.h"
#include <iostream>
#include "Globals.h"
#include "Inventory.h"
#include "PopupScene.h"

int main()
{
    Globals::font = new sf::Font();
    Globals::font->loadFromFile("Files/other/FFFForward.TTF");
    Globals::popupBoxTex = new sf::Texture();
    Globals::popupBoxTex->loadFromFile("Files/global/basic_popup_box.png");

    Game johnson;
    Inventory::readFiles();
    johnson.run(new MenuScene());
    //Globals::save = new Save("pula", true);
    //johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}