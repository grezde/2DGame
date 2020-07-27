#include "Game.h"
#include "WalkingScene.h"
#include "Save.h"

int main()
{
    Game johnson;
    johnson.run(new WalkingScene("johnson_classroom"));
    return 0;
}