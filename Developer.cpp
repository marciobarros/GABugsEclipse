#include "stdafx.h"
#include "Developer.h"
#include <string.h>

Developer::Developer(int index, std::string name, std::string email)
{
	this->name = name;
	this->email = email;
	this->index = index;
}

Developer::~Developer(void)
{
}

const char * Developer::getEmail ()
{
	return this->email.c_str();
}

const char * Developer::getName()
{
	return this->name.c_str(); 
}

void Developer::addBug (Bug *bug)
{
	this->bugList.push_back (bug);	
}

int Developer::getNumberOfBugs (void)
{
	return (int) bugList.size();
}

Bug *Developer::getBug(int index)
{
	return bugList[index];
}

void Developer::removeBug (int index) 
{
	if (index >=  (int) bugList.size())
		return;
	bugList.erase (bugList.begin()+index);
}

double Developer::calculateCost (bool sort)
{
	double cost = 0;
	int time=0;
	int weight=0;

	if (sort)
		this->sortBugs();

	for (unsigned i=0; i < bugList.size(); i++)
	{
		Bug *bug = bugList [i];
		time = time + bug->getEffortTime();
		int weight = MAX_BUG_PRIORITY - bug->getPriority() + 1;
		cost = cost + (time * weight);
	}

	return cost;
}

int Developer::calculateMakespan()
{
	int time=0;
	for (unsigned i=0; i < bugList.size(); i++)
		time = time + bugList[i]->getEffortTime();
	return time;
}

int Developer::getIndex()
{
	return index;
}

void Developer::quicksortBugs (int l, int r)
{
	int i = l;
	int j = r;
	int mid = (l + r) / 2;
	double x = bugList[mid]->calculateSmithRatio();

	do
	{
		while (bugList[i]->calculateSmithRatio() < x)
			i++;

		while (x < bugList[j]->calculateSmithRatio())
			j--;

		if (i <= j)
		{
			Bug *aux = bugList[i];
			bugList[i] = bugList[j];
			bugList[j] = aux;
			i++;
			j--;
		}

	} while (i <= j);

	if (l < j)
		quicksortBugs(l, j);

	if (i < r)
		quicksortBugs(i, r);
}

void Developer::sortBugs ()
{
	if (bugList.size() > 0)
		quicksortBugs (0, bugList.size()-1);
}