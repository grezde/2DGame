#include "Action.h"

#include "RenderAction.h"
#include "InteractAction.h"
#include "TeleportAction.h"
#include "StartAction.h"
#include "ConditionAction.h"
#include "VariableAction.h"

Action* Action::getActionClass(char code, std::vector<std::string> data)
{
	if (code == 'i')
		return new RenderAction(data);
	if (code == 'a')
		return new InteractAction(data);
	if (code == 't')
		return new TeleportAction(data);
	if (code == 's')
		return new StartAction(data);
	if (code == 'b')
		return new ConditionAction(data);
	if (code == 'v')
		return new VariableAction(data);

	return new Action(data);
}

Action* Action::readFromStream(std::istream& fin)
{
	std::string s;
	std::vector<std::string> text;
	char code;
	int nrLines;
	fin >> nrLines >> code;
	std::getline(fin, s);
	for (int k = 0; k < nrLines; k++) {
		std::getline(fin, s);
		text.push_back(s);
	}

	Action* a = getActionClass(code, text);
	a->onRead(fin);

	return a;
}
