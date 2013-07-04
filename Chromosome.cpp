#include "StdAfx.h"
#include "Chromosome.h"
#include "Developer.h"

Chromosome::Chromosome (HistoricalData *historicalData, std::vector <double> genes)
{
	this->historicalData = historicalData;
	this->genes = genes;
	createSchedule ();
}

Chromosome::~Chromosome(void)
{
	try
	{
		delete schedule;
	}
	catch (...) 
	{

	}
}

void Chromosome::createSchedule ()
{
	schedule = new Schedule (historicalData->developerList, historicalData->openBugList);

	for (unsigned i = 0; i < historicalData->openBugList.size (); i++)
	{
		int index = historicalData->getDeveloperIndex (historicalData->openBugList[i]->getClassIndex(), genes [i]);
		schedule->developerList [index]->addBug (historicalData->openBugList[i]);
	}

	this->cost = schedule->calculateCost (true);
}

Schedule *Chromosome::getSchedule ()
{
	return schedule;
}

double Chromosome::getGene (int index)
{
	return this->genes [index];
}

double Chromosome::getCost()
{
	return cost;
}

Chromosome *Chromosome::clone ()
{
	return new Chromosome (historicalData, genes);
}

void Chromosome::swapGene (int index1, int index2)
{
	double gene1 = this->genes [index1];
	double gene2 = this->genes [index2];
	this->genes [index1] = gene2;
	this->genes [index2] = gene1;
}

void Chromosome::recalculateSchedule ()
{
	delete schedule;
	createSchedule ();
}