#include "Game.h"
#include "Globals.h"
#include "MenuScene.h"
#include "WalkingScene.h"
#include <iostream>
#include "VariableConditionParser.h"

int main()
{
    VariableConditionParser vcp("first_locker_broken 0 1 2 3-4 5");
    Globals::init();

    Game johnson;
    johnson.run(new MenuScene());
    //Globals::save = new Save("pula", true);
    //johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}