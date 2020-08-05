#include "Game.h"
#include "WalkingScene.h"
#include "MenuScene.h"
#include <iostream>
#include "Globals.h"
#include "Inventory.h"

int main()
{
    Game johnson;
    Inventory::readFiles();
    johnson.run(new MenuScene());
    //Globals::save = new Save("pula", true);
    //johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}