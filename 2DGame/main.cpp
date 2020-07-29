#include "Game.h"
#include "WalkingScene.h"
#include "Save.h"
#include "SpeechManager.h"

int main()
{
    Game johnson;
    johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}