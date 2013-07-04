#include "StdAfx.h"
#include "LocalSearch.h"
#include "random.h"

LocalSearch::LocalSearch(HistoricalData *historicalData, int maxEvaluations)
{
	this->historicalData = historicalData;
	this->maxEvaluations = maxEvaluations;
}

LocalSearch::~LocalSearch(void)
{
}

Chromosome *LocalSearch::run ()
{
	// Creates a random chromossome
	std::vector <double> genes;
	
	for (unsigned k = 0; k < historicalData->openBugList.size(); k++) 
		genes.push_back (rand_uniform());

	// Calculate cost and chromossome size
	Chromosome *chromosome = new Chromosome (historicalData, genes);
	double costReference = chromosome->getCost();
	int evaluations = 1;

	// Hill Climbing local search
	int size = chromosome->genes.size();
	Chromosome *neighbour = chromosome->clone();

	while (evaluations <= maxEvaluations)
	{
		int i = 0, j;

		while (i < size && evaluations <= maxEvaluations)
		{
			for (j = i + 1; j < size && evaluations <= maxEvaluations; j++)
			{
				neighbour->swapGene(i, j);
				neighbour->recalculateSchedule();
				evaluations++;
				
				if (neighbour->getCost() < costReference) 
				{
					delete chromosome;
					chromosome = neighbour;
					costReference = neighbour->getCost();
					neighbour = neighbour->clone();
					break;
				}
				else
					neighbour->swapGene (j, i);
			}

			i = j;
		}

		// Creates new random chromossome
		genes.clear();

		for (unsigned k = 0; k < historicalData->openBugList.size(); k++) 
			genes.push_back (rand_uniform());

		// Calculate cost and chromossome size
		delete neighbour;
		neighbour = new Chromosome (historicalData, genes);
		evaluations++;

		if (neighbour->getCost() < costReference) 
		{
			delete chromosome;
			chromosome = neighbour;
			costReference = neighbour->getCost();
			neighbour = neighbour->clone();
		}
	}

	return chromosome;
}