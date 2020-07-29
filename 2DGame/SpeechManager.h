#pragma once
#include "Scene.h"

class SpeechContainer 
{
public:
	enum Type
	{
		Line,
		Choice
	};
	typedef std::vector<std::string>::iterator iter;
	static std::vector<SpeechContainer*> parse(iter start, iter end);
	
	Type type;
	SpeechContainer(Type t) 
		: type(t) {}
	
};

class LineSC : public SpeechContainer
{
public:
	std::string text;
	LineSC() : SpeechContainer(Line) {}
};

class ChoiceSC : public SpeechContainer
{
public:
	std::string question;
	std::vector<std::string> choiceTexts;
	std::vector<std::vector<SpeechContainer*>> choices;
	
	ChoiceSC() : SpeechContainer(Choice) {}
	~ChoiceSC();
};

class SpeechManager
{
public:
	enum State
	{
		Writing,
		Finished,
		WritingMenuText,
		WritingMenuOptions,
		Selecting,
		Pause
	};

private:
	State s;
	std::string text;
	int index;
	std::vector<SpeechContainer*> script;

public:
	SpeechManager(std::vector<std::string> lines);

	void update(float dt);

	inline State state() { return s; }

};

