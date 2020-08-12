#pragma once
#include <string>
#include <vector>
#include "ConditionParser.h"

class ChainSC;

class SpeechContainer
{
private:
	static bool specialCharacter(char c);

public:
	enum Type
	{
		Line,
		Choice,
		Chain,
		Execute,
		Metadata,
		Prompt,
		GameCondition
	};
	typedef std::vector<std::string>::iterator iter;
	static ChainSC* parse(iter start, iter end);

private:
	Type t;

public:
	int index;

public:
	SpeechContainer(Type t)
		: t(t), index(0) {}

	inline Type type() { return t; }
};

class LineSC : public SpeechContainer
{
public:
	std::string text;
	LineSC() : SpeechContainer(Line) {}
};

class ChainSC : public SpeechContainer
{
public:
	std::vector<SpeechContainer*> chain;

	ChainSC(std::vector<SpeechContainer*> vect)
		: chain(vect), SpeechContainer(Chain) {}
	~ChainSC();
};

class ChoiceSC : public SpeechContainer
{
public:
	std::string question;
	std::vector<std::string> choiceTexts;
	std::vector<ChainSC*> choices;

	ChoiceSC() : SpeechContainer(Choice) {}
	~ChoiceSC();
};

class Action;

class ExecuteSC : public SpeechContainer
{
public:
	Action* action = nullptr;
	
	ExecuteSC() : SpeechContainer(Execute) {}
	~ExecuteSC();
};

class MetadataSC : public SpeechContainer
{
public:
	std::string metadata;

	MetadataSC() : SpeechContainer(Metadata) {}
};

class PromptSC : public SpeechContainer
{
public:
	std::string question;
	std::string varname;

	PromptSC() : SpeechContainer(Prompt) {}
};

class GameConditionSC : public SpeechContainer
{
public:
	ConditionParser* parser = nullptr;
	std::vector<ChainSC*> choices;

	GameConditionSC() : SpeechContainer(GameCondition) {}
	~GameConditionSC();
};