#include "Game.h"
#include "Globals.h"
#include "MenuScene.h"
#include "WalkingScene.h"
#include <iostream>

int main()
{
    Globals::init();

    Game johnson;
    johnson.run(new MenuScene());
    //Globals::save = new Save("pula", true);
    //johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}