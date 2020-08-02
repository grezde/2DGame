#pragma once
#include "Scene.h"
#include "SpeechManager.h"

class SpeechCutScene :
	public Scene, public SpeechManager
{
private:

public:
	SpeechCutScene(std::vector<std::string> data);
	SpeechCutScene(std::string filename);
};

