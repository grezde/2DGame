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
	stack.push_back(script);
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
	stack.push_back(script);
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
			LineSC* line = ((LineSC*)(stack.back()));
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
			ChoiceSC* ch = ((ChoiceSC*)(stack.back()));
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
			ChoiceSC* ch = ((ChoiceSC*)(stack.back()));
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
			ExecuteSC* exc = ((ExecuteSC*)(stack.back()));
			exc->action->trigger();
			Game::curent()->updateAllScenes();
			s = RequestNext;
		}
		else if (s == ProcessMetadata) {
			s = RequestNext;
		}
		else if (s == WritingPromptText) {
			PromptSC* psc = ((PromptSC*)(stack.back()));
			if (psc->index == psc->question.size()) {
				submitted.clear();
				text = "_";
				s = ReadingPrompt;
				return;
			}
			text += psc->question[psc->index];
			psc->index++;
		}
		else if (s == ReadingPrompt) {
			if (text == "_")
				text = " ";
			else
				text = "_";
		}
		else if (s == RequestNext) {
			text.clear();
			while (!stack.empty() && stack.back()->type() != SpeechContainer::Chain) {
				stack.back()->index = 0;
				stack.pop_back();
			}
			while (!stack.empty() && stack.back()->type() == SpeechContainer::Chain) {
				ChainSC* chain = ((ChainSC*)(stack.back()));
				if (chain->index < chain->chain.size()) {
					chain->index++;
					stack.push_back(chain->chain[chain->index-1]);
					break;
				} 
				else {
					stack.back()->index = 0;
					stack.pop_back();
				}
			}
			//at the top of the stack there must be a non chain element
			//or an empty stack
			if (stack.empty()) {
				s = Finished;
				return;
			}
			if (stack.back()->type() == SpeechContainer::Line)
				s = Writing;
			else if (stack.back()->type() == SpeechContainer::Choice)
				s = WritingMenuText;
			else if (stack.back()->type() == SpeechContainer::Execute)
				s = Executing;
			else if (stack.back()->type() == SpeechContainer::Metadata)
				s = ProcessMetadata;
			else if (stack.back()->type() == SpeechContainer::Prompt)
				s = WritingPromptText;
			return;
		}
	}
}

void SpeechManager::proceed(int option)
{
	if(s == Pause)
		s = RequestNext;
	if (s == Selecting) {
		ChoiceSC* ch = ((ChoiceSC*)(stack.back()));
		stack.pop_back();
		stack.push_back(ch->choices[option]);
		s = RequestNext;
	}
}

std::string SpeechManager::displayText()
{
	if(s == ReadingPrompt)
		return ">  " + submitted + text;
	return text;
}

int SpeechManager::numberOfOptions()
{
	if (s == WritingMenuText || s == WritingMenuOptions || s == Selecting)
		return ((ChoiceSC*)(stack.back()))->choiceTexts.size();
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
		return ((MetadataSC*)(stack.back()))->metadata;
	return "";
}

void SpeechManager::submitChar(char c)
{
	if (s != ReadingPrompt)
		return;

	if (c == 8) {
		if (submitted.size() != 0)
			submitted.pop_back();
	}
	else if (c == 13) {
		std::string varname = ((PromptSC*)(stack.back()))->varname;
		if (varname == "save_name") {
			if (Globals::save != nullptr)
				delete Globals::save;
			Globals::save = new Save(submitted, false);
		}
		else
			Globals::save->sets(varname, submitted);
		s = RequestNext;
	}
	else if(c != ' ')
		submitted += c;

}
