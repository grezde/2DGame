#pragma once
#include <string>
#include <vector>
#include <istream>

class ConditionParser
{
public:
	virtual int nChoices() = 0;
	virtual int getChoice() = 0;

	static ConditionParser* getParser(std::string condition);
};

class BooleanConditionParser
	: public ConditionParser
{
public:
	virtual int nChoices() override { return 2; };
};

class IntervalConditionParser
	: public ConditionParser
{
public:
	typedef struct {
		int min;
		int max;
	} Interval;

protected:
	std::vector<Interval> intervals;

protected:
	int getIntervalIndex(int value);
	void readIntervals(std::istream& in);

public:
	virtual int nChoices() override { return intervals.size(); }
};

