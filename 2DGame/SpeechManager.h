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
		
		WritingMenuText,
		WritingMenuOptions,
		Selecting,
		
		Executing,
		
		WritingPromptText,
		ReadingPrompt,

		ProcessMetadata,

		RequestNext,
		Finished,
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

private:
	std::string parseString(std::string s);

public:
	SpeechManager(std::vector<std::string> lines);
	SpeechManager(std::string sequenceFilename);
	void updateState(float dt);

	inline State state() { return s; }
	inline std::string displayText() { return text; }
	
	int numberOfOptions();
	int curentOptionWriten();
	void proceed(int option = -1);

	std::string getMetadata();

	void submitString(std::string s);
};

