#pragma once
#include <string>
#include <vector>

class ChainSC;

class SpeechContainer
{
public:
	enum Type
	{
		Line,
		Choice,
		Chain,
		Execute
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
	Action* action;
	
	ExecuteSC() : SpeechContainer(Execute) {};
	~ExecuteSC();
};
