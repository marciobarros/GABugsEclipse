#include "StdAfx.h"
#include "Schedule.h"

//int contador = 0;

Schedule::Schedule()
{
}

Schedule::Schedule(std::vector <Developer*> developers, std::vector <Bug*> bugList)
{
	this->bugList = bugList;

	for (unsigned i = 0; i < developers.size (); i++)
		this->developerList.push_back (new Developer (developers[i]->getIndex(), developers [i]->getName(), developers [i]->getEmail()));
}

Schedule::~Schedule(void)
{
	int size = (int) (developerList.size ());

	for (int j = size-1; j >= 0; j--) 
	{
		Developer *developer = developerList [j];
		developerList.pop_back ();
		delete developer;
	}
}

void Schedule::addDeveloper (Developer *developer)
{
	this->developerList.push_back (developer);
}

Developer *Schedule::getDeveloper (const char *developerName)
{
	for (unsigned i = 0; i < developerList.size(); i++)
	{
		Developer *developer = developerList[i];
		std::string name = developer->getName();

		if (!name.compare (developerName))
			return developer;
	}

	return NULL;
}

double Schedule::calculateCost (bool sort)
{
	double cost = 0;
	//printf("%d ...\r", ++contador);

	for (unsigned i = 0; i < this->developerList.size (); i++) 
		cost += developerList [i]->calculateCost (sort);

	return cost;
}

int Schedule::calculateMakespan ()
{
	int makespan = 0;

	for (unsigned i = 0; i < this->developerList.size (); i++) 
	{
		int aux = developerList [i]->calculateMakespan ();

		if (aux > makespan)
			makespan = aux;
	}

	return makespan;
}

void Schedule::assignBug (int indexDeveloper, int indexBug) 
{
	Developer *developer = this->developerList [indexDeveloper];

	if ((unsigned)indexBug < bugList.size()) 
	{
		Bug *bug  = this->bugList [indexBug];
		developer->addBug (bug);
	}
}

int Schedule::getNumberOfDevelopers ()
{
	return developerList.size ();
}

Developer *Schedule::getDeveloper (int indexDeveloper)
{
	if (indexDeveloper < (int) developerList.size ())
		return developerList [indexDeveloper];
	else
		return NULL;
}