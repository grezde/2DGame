#include "SpeechCutScene.h"

SpeechCutScene::SpeechCutScene(std::vector<std::string> data)
	: SpeechManager(data)
{

}

SpeechCutScene::SpeechCutScene(std::string filename)
	: SpeechManager(filename)
{

}
