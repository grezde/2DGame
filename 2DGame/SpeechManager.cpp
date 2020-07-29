#include "SpeechManager.h"
#include <sstream>

SpeechManager::SpeechManager(std::vector<std::string> lines)
{
	script = SpeechContainer::parse(lines.begin(), lines.end());
	;;;
}

void SpeechManager::update(float dt)
{

}

std::vector<SpeechContainer*> SpeechContainer::parse(iter start, iter end)
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
	return script;
}

ChoiceSC::~ChoiceSC()
{
	for (std::vector<SpeechContainer*> v : choices)
		for (SpeechContainer* vv : v)
			delete vv;
}
