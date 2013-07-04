#pragma once

#include "Chromosome.h"
#include "Bug.h"
#include "Developer.h"
#include "historicaldata.h"
#include <vector>

class LocalSearch
{
	private:
	HistoricalData *historicalData;
	int maxEvaluations;

	public:
	LocalSearch(HistoricalData *historicalData, int maxEvaluations);
	~LocalSearch(void);
	Chromosome *run();
};