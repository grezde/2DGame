#include "Game.h"
#include "WalkingScene.h"
#include "MenuScene.h"
#include "SpeechCutScene.h"

int main()
{
    Game johnson;
    johnson.run(new MenuScene());
    //johnson.run(new SpeechCutScene("welcome"));
    //johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}