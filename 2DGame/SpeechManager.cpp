#include "SpeechManager.h"
#include "Action.h"
#include "Game.h"
#include "Globals.h"
#include <sstream>
#include <iostream>

std::string SpeechManager::parseString(std::string s)
{
	if (Globals::save == nullptr)
		return s;

	int index;
	std::string varname, varvalue;
	while ((index = s.find('$')) != std::string::npos) {
		std::istringstream(s.substr(index + 1)) >> varname;
		varvalue = Globals::save->get(varname);
		s.replace(s.begin() + index, s.begin() + index + varname.size() + 2, varvalue);
	}
	return s;
}

SpeechManager::SpeechManager(std::vector<std::string> lines)
{
	script = SpeechContainer::parse(lines.begin(), lines.end());
	scque.push(script);
	s = RequestNext;
}

SpeechManager::SpeechManager(std::string filename)
{
	std::vector<std::string> vs;
	std::ifstream fin(filename);
	while (!fin.eof()) {
		std::string s;
		std::getline(fin, s);
		vs.push_back(s);
	}
	script = SpeechContainer::parse(vs.begin(), vs.end());
	scque.push(script);
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
			if (line->index == line->text.size()) {
				s = Pause;
				return;
			}
			if (line->index == 0) {
				line->text = parseString(line->text);
			}
			text += line->text[line->index];
			line->index++;
		}
		else if (s == WritingMenuText) {
			ChoiceSC* ch = ((ChoiceSC*)(scque.top()));
			if (ch->index == ch->question.size()) {
				s = WritingMenuOptions;
				ch->index = 0;
				optionIndex = 0;
				text.clear();
				return;
			}
			text += ch->question[ch->index];
			ch->index++;
		}
		else if (s == WritingMenuOptions) {
			ChoiceSC* ch = ((ChoiceSC*)(scque.top()));
			if (ch->index == ch->choiceTexts[optionIndex].size()) {
				optionIndex++;
				text.clear();
				ch->index = 0;
				if (optionIndex == ch->choices.size()) {
					s = Selecting;
					return;
				}
			}
			text += ch->choiceTexts[optionIndex][ch->index];
			ch->index++;
		}
		else if (s == Executing) {
			ExecuteSC* exc = ((ExecuteSC*)(scque.top()));
			exc->action->trigger();
			Game::curent()->updateAllScenes();
			s = RequestNext;
		}
		else if (s == ProcessMetadata) {
			s = RequestNext;
		}
		else if (s == WritingPromptText) {
			PromptSC* psc = ((PromptSC*)(scque.top()));
			if (psc->index == psc->question.size()) {
				s = ReadingPrompt;
				return;
			}
			text += psc->question[psc->index];
			psc->index++;
		}
		else if (s == RequestNext) {
			text.clear();
			while (!scque.empty() && scque.top()->type() != SpeechContainer::Chain) {
				scque.top()->index = 0;
				scque.pop();
			}
			while (!scque.empty() && scque.top()->type() == SpeechContainer::Chain) {
				ChainSC* chain = ((ChainSC*)(scque.top()));
				if (chain->index < chain->chain.size()) {
					chain->index++;
					scque.push(chain->chain[chain->index-1]);
					break;
				} 
				else {
					scque.top()->index = 0;
					scque.pop();
				}
			}
			//at the top of the stack there must be a non chain element
			//or an empty stack
			if (scque.empty()) {
				s = Finished;
				return;
			}
			if (scque.top()->type() == SpeechContainer::Line)
				s = Writing;
			else if (scque.top()->type() == SpeechContainer::Choice)
				s = WritingMenuText;
			else if (scque.top()->type() == SpeechContainer::Execute)
				s = Executing;
			else if (scque.top()->type() == SpeechContainer::Metadata)
				s = ProcessMetadata;
			else if (scque.top()->type() == SpeechContainer::Prompt)
				s = WritingPromptText;
		}
	}
}

void SpeechManager::proceed(int option)
{
	if(s == Pause)
		s = RequestNext;
	if (s == Selecting) {
		ChoiceSC* ch = ((ChoiceSC*)(scque.top()));
		scque.pop();
		scque.push(ch->choices[option]);
		s = RequestNext;
	}
}

int SpeechManager::numberOfOptions()
{
	if (s == WritingMenuText || s == WritingMenuOptions || s == Selecting)
		return ((ChoiceSC*)(scque.top()))->choiceTexts.size();
	return 0;
}

int SpeechManager::curentOptionWriten()
{
	if (s == WritingMenuOptions)
		return optionIndex;
	return -1;
}

std::string SpeechManager::getMetadata()
{
	if (s == ProcessMetadata)
		return ((MetadataSC*)(scque.top()))->metadata;
	return "";
}

void SpeechManager::submitString(std::string str)
{
	if (s == ReadingPrompt) {
		std::string varname = ((PromptSC*)(scque.top()))->varname;
		if (varname == "save_name") {
			if (Globals::save != nullptr)
				delete Globals::save;
			Globals::save = new Save(str, true);
		}
		else
			Globals::save->sets(varname, str);
		s = RequestNext;
	}
}
