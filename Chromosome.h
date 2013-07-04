#pragma once

#include <vector>
#include "Developer.h"
#include "Bug.h"
#include "Schedule.h"
#include "historicaldata.h"

#define MAX_RAND 10000

class Chromosome
{
	private:
	HistoricalData *historicalData;
	Schedule *schedule;
	double cost;

	private:
	void createSchedule ();

	public:
	std::vector <double> genes;
	Chromosome (HistoricalData *historicalData, std::vector <double> genes);
	Schedule *getSchedule ();
	void recalculateSchedule ();
	double getGene (int index);
	Chromosome *clone ();
	double getCost ();
	void swapGene (int index1, int index2);
	~Chromosome(void);
};