#include "Game.h"
#include "WalkingScene.h"
#include "Save.h"
#include "SpeechManager.h"

int main()
{
    std::vector<std::string> text = {
        "* Lockerul asta are foarte multe fisuri",
        "in el. Aproape ca ai putea sa il ",
        "* deschizi fara sa il spargi.",
        "> Incerci sa il deschizi ?",
        "  2 9 2", 
        "> Da",
        "> Nu",
        "* L-ai desfacut cu usurinta. Te uiti",
        "inauntru si vezi un fular.",
        "> Furi fularul ?",
        "  2 2 1",
        "> Da",
        "> Nu",
        "* Ai obtinut fularul! Verifica in inventar.",
        "* Golanule.",
        "* Lasi fularul acolo.",
        "* Decizi sa nu deschizi lockerul. Poate",
        "ai facut o alegere buna."
    };
    std::vector<SpeechContainer*> script = SpeechContainer::parse(text.begin(), text.end());
    script;
    Game johnson;
    johnson.run(new WalkingScene("hol_etaj_3"));
    return 0;
}