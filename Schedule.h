#pragma once

#include "Developer.h"
#include "Bug.h"
#include <vector>

class Schedule
{
public:
	std::vector <Developer*> developerList;
	std::vector <Bug*> bugList;
public:
	Schedule();
	Schedule(std::vector <Developer*> developers, std::vector <Bug*> bugList);
	~Schedule(void);
	double calculateCost (bool sort);
	int calculateMakespan ();
	void assignBug (int indexDeveloper, int indexBug);
	void addDeveloper (Developer *developer);
	Developer *getDeveloper (const char *developerName);
	int getNumberOfDevelopers ();
	Developer *getDeveloper (int indexDeveloper);
};