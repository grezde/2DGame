#include "SpeechManager.h"
#include <sstream>
#include <iostream>

SpeechManager::SpeechManager(std::vector<std::string> lines)
{
	script = SpeechContainer::parse(lines.begin(), lines.end());
	scque.push(script);
	std::cout << "\nINITIAL " << (scque.top()->type() == SpeechContainer::Chain ? "CHAIN" : scque.top()->type() == SpeechContainer::Line ? "LINE" : "CHOICE") << "\n";
	s = RequestNext;
}

void SpeechManager::updateState(float dt)
{
	if (s == Finished)
		return;

	accum += dt;
	while (accum > interval) {
		accum -= interval;
		if (s == Writing) {
			LineSC* line = ((LineSC*)(scque.top()));
			text += line->text[line->index];
			line->index++;
			if (line->index == line->text.size()) {
				s = Pause;
				return;
			}
		}
		if (s == WritingMenuText) {
			ChoiceSC* ch = ((ChoiceSC*)(scque.top()));
			text += ch->question[ch->index];
			ch->index++;
			if (ch->index == ch->question.size()) {
				s = Pause;
				return;
			}
		}
		if (s == RequestNext) {
			text.clear();
		
			while (!scque.empty() && scque.top()->type() != SpeechContainer::Chain)
				scque.pop();
			while (!scque.empty() && scque.top()->type() == SpeechContainer::Chain) {
				ChainSC* chain = ((ChainSC*)(scque.top()));
				if (chain->index < chain->chain.size()) {
					chain->index++;
					scque.push(chain->chain[chain->index-1]);
					std::cout << "ADD " << (scque.top()->type() == SpeechContainer::Chain ? "CHAIN" : scque.top()->type() == SpeechContainer::Line ? "LINE" : "CHOICE") << "\n";
					break;
				} 
				else {
					std::cout << "POP " << (scque.top()->type() == SpeechContainer::Chain ? "CHAIN" : scque.top()->type() == SpeechContainer::Line ? "LINE" : "CHOICE") << "\n";
					scque.pop();
				}
			}
			//at the end of the queue there must be a non chain element
			//or an empty queue
			if (scque.empty()) {
				s = Finished;
				return;
			}
			if (scque.top()->type() == SpeechContainer::Line)
				s = Writing;
			else if (scque.top()->type() == SpeechContainer::Choice)
				s = WritingMenuText;
		}
	}
}

void SpeechManager::proceed(int option)
{
	if(s == Pause)
		s = RequestNext;
}

ChainSC* SpeechContainer::parse(iter start, iter end)
{
	std::vector<SpeechContainer*> script;
	for (iter i = start; i < end;) {
		if (i->at(0) == '*') {
			LineSC* lsc = new LineSC();
			lsc->text = i->substr(2);
			i++;
			while (i < end && i->at(0) != '*' && i->at(0) != '>') {
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
			iter now=i+nr+1;
			for (int k = 1; k <= nr; k++) {
				iss >> a;
				csc->choiceTexts.push_back((i + k)->substr(2));
				csc->choices.push_back(parse(now, now + a));
				now = now + a;
			}
			script.push_back(csc);
			i = now;
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
