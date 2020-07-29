#include "SpeechContainer.h"
#include "Action.h"
#include <sstream>

ChainSC* SpeechContainer::parse(iter start, iter end)
{
	std::vector<SpeechContainer*> script;
	for (iter i = start; i < end;) {
		if (i->at(0) == '*') {
			LineSC* lsc = new LineSC();
			lsc->text = i->substr(2);
			i++;
			while (i < end && i->at(0) != '*' && i->at(0) != '>' && i->at(0) != '/') {
				lsc->text += "\n" + *i;
				i++;
			}
			script.push_back(lsc);
		}
		else if (i->at(0) == '>') {
			ChoiceSC* csc = new ChoiceSC();
			int nr, a;
			csc->question = i->substr(2);
			i++;
			std::istringstream iss(*i);
			iss >> nr;
			iter now = i + nr + 1;
			for (int k = 1; k <= nr; k++) {
				iss >> a;
				csc->choiceTexts.push_back((i + k)->substr(2));
				csc->choices.push_back(parse(now, now + a));
				now = now + a;
			}
			script.push_back(csc);
			i = now;
		}
		else if (i->at(0) == '/') {
			ExecuteSC* exc = new ExecuteSC();
			int n;
			std::istringstream(i->substr(2)) >> n;
			std::string all = i->substr(2);
			for (iter it = i + 1; it < i + n + 1; it++)
				all += "\n" + (*it);
			i = i + n + 1;
			std::istringstream iss(all);
			exc->action = Action::readFromStream(iss);
			script.push_back(exc);
		}
	}
	return new ChainSC(script);
}

ChoiceSC::~ChoiceSC()
{
	for (ChainSC* c : choices)
		delete c;
}

ChainSC::~ChainSC()
{
	for (SpeechContainer* sc : chain)
		delete sc;
}

ExecuteSC::~ExecuteSC()
{
	delete action;
}