#pragma once

#include "Chromosome.h"
#include "Bug.h"
#include "Developer.h"
#include "historicaldata.h"
#include <vector>

#define CROSSOVER_PROBABILITY_PARAMETER 70
#define TOPMOST_PERCENTIL 0.20
#define NEW_PERCENTIL 0.79

class RandomKeyMethod
{
	private:
	HistoricalData *historicalData;
	std::vector <Chromosome *> population;
	int populationSize;

	private:
	void quicksortPopulation (int l, int r);
	void sortPopulation ();
	Chromosome *createMutant ();
	Chromosome *crossover (Chromosome *parent1, Chromosome *parent2);

	public:
	RandomKeyMethod (HistoricalData *historicalData, int populationSize);
	~RandomKeyMethod(void);
	void reproduct ();
	Chromosome *getBestSolution ();
};