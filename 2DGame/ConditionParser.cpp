#include "ConditionParser.h"
#include <iostream>
#include <sstream>
#include "Save.h"

#include "VariableConditionParser.h"

ConditionParser* ConditionParser::getParser(std::string condition)
{
	std::string start;
	std::istringstream(condition) >> start;
	condition = condition.substr(start.size() + 1);

	if (start == "var")
		return new VariableConditionParser(condition);

	return nullptr;
}


int IntervalConditionParser::getIntervalIndex(int value)
{
	for (int i = 0; i < intervals.size(); i++)
		if (intervals[i].min <= value && value <= intervals[i].max)
			return i;
	return -1;
}

void ingetc(std::istream& in, char& c)
{
	char z;
	in.get(z);
	if (in.eof())
		c = ' ';
	else
		c = z;
}

void IntervalConditionParser::readIntervals(std::istream& in)
{
	char c;
	int mult = 1, nr = 0, nr2=0;

	ingetc(in, c);
	while (!in.eof()) {
		while (c == ' ') {
			if (in.eof())
				return;
			ingetc(in, c);
		}

		Interval i;
		if (c == '-') {
			nr = 0;
			mult = -1;
		}
		else {
			nr = c - '0';
			mult = 1;
		}
		
		ingetc(in, c);
		while ('0' <= c && c <= '9') {
			nr = 10 * nr + (c - '0');
			ingetc(in, c);
		}
		nr *= mult;
		if (c == '-') {
			ingetc(in, c);
			if (c == ' ') {
				i.min = -Save::MAXINT;
				i.max = nr;
				ingetc(in, c);
			}
			else {
				if (c == '-') {
					nr2 = 0;
					mult = -1;
				}
				else if ('0' <= c && c <= '9') {
					nr2 = c - '0';
					mult = 1;
				}

				ingetc(in, c);
				while ('0' <= c && c <= '9') {
					nr2 = 10 * nr2 + (c - '0');
					if (in.eof())
						break;
					ingetc(in, c);
				}
				nr2 *= mult;
				i.min = nr;
				i.max = nr2;
			}
		}
		else if (c == '+') {
			i.min = nr;
			i.max = Save::MAXINT;
			ingetc(in, c);
		}
		else
			i.min = i.max = nr;
		intervals.push_back(i);
	}
}