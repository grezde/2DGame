#pragma once
#include "SpeechCutScene.h"
#include "WalkingScene.h"

class WelcomeSCS
	: public SpeechCutScene
{
public:
	WelcomeSCS() : SpeechCutScene("welcome") {};
	
	virtual void onFinished() override;

};