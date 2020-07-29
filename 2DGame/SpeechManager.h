#pragma once
#include "Scene.h"
#include "SpeechContainer.h"
#include <queue>
#include <stack>

class SpeechManager
{
public:
	enum State
	{
		Writing,
		Pause,
		RequestNext,
		WritingMenuText,
		WritingMenuOptions,
		Selecting,
		Finished,
		Executing
	};

private:
	State s;
	std::string text;
	int index;
	ChainSC* script;
	std::stack<SpeechContainer*> scque;
	float accum = 0.0f;
	int optionIndex = 0;

protected:
	float interval = 0.0f;

public:
	SpeechManager(std::vector<std::string> lines);
	void updateState(float dt);

	inline State state() { return s; }
	inline std::string displayText() { return text; }
	void proceed(int option = -1);
	int numberOfOptions();
	int curentOptionWriten();
};

