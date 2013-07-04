#include "StdAfx.h"
#include "RandonKeyMethod.h"
#include "random.h"

RandomKeyMethod::RandomKeyMethod (HistoricalData *historicalData, int populationSize)
{
	this->historicalData = historicalData;
	this->populationSize = populationSize;

	for (int i=0; i < this->populationSize; i++) 
		population.push_back (createMutant ());

	sortPopulation ();
}

RandomKeyMethod::~RandomKeyMethod(void)
{
}

void RandomKeyMethod::quicksortPopulation (int l, int r)
{
	int i = l;
	int j = r;
	int mid = (l + r) / 2;
	double x = population[mid]->getCost();

	do
	{
		while (population[i]->getCost() < x)
			i++;

		while (x < population[j]->getCost())
			j--;

		if (i <= j)
		{
			Chromosome *aux = population[i];
			population[i] = population[j];
			population[j] = aux;
			i++;
			j--;
		}

	} while (i <= j);

	if (l < j)
		quicksortPopulation(l, j);

	if (i < r)
		quicksortPopulation(i, r);
}

void RandomKeyMethod::sortPopulation ()
{
	quicksortPopulation(0, populationSize - 1);
}

Chromosome *RandomKeyMethod::createMutant ()
{
	std::vector <double> genes;
	
	for (unsigned i=0; i < historicalData->openBugList.size (); i++) 
		genes.push_back (rand_uniform());

	return (new Chromosome (historicalData, genes));
}

Chromosome *RandomKeyMethod::crossover (Chromosome *parent1, Chromosome *parent2)
{
	std::vector <double> offspring;

	for (unsigned i=0; i < historicalData->openBugList.size (); i++) 
	{
		double randomNumber = rand_uniform() * 100;

		if (randomNumber <= CROSSOVER_PROBABILITY_PARAMETER)
			offspring.push_back (parent1->getGene (i));
		else
			offspring.push_back (parent2->getGene (i));
	}

	return (new Chromosome (historicalData, offspring));
}

void RandomKeyMethod::reproduct ()
{
	int topBound = (int) (TOPMOST_PERCENTIL * populationSize);
	std::vector <Chromosome *> nextPopulation;

	for (int i = 0; i < topBound; i++) 
		nextPopulation.push_back (population [i]);

	int crossoverBound = (int) (NEW_PERCENTIL * populationSize);	

	for (int i = 0; i < crossoverBound; i++)
	{
		int choiceParent1 = (int) (rand_uniform() * topBound);
		Chromosome *parent1 = (nextPopulation) [choiceParent1];
			
		int choiceParent2 = (int) (rand_uniform() * populationSize);
		Chromosome *parent2 = population [choiceParent2];

		Chromosome *offspring = this->crossover (parent1, parent2);
		nextPopulation.push_back (offspring);
	}
	
	int mutantBound = (int) (populationSize - nextPopulation.size ());

	for (int i = populationSize-1; i >= topBound; i--)
	{
		Chromosome *chromosome = population [i];
		population.pop_back ();
		delete chromosome;
	}

	for (int i = 0; i < mutantBound; i++)
		nextPopulation.push_back (createMutant ());

	population.swap (nextPopulation);		
	sortPopulation ();
}
		
Chromosome *RandomKeyMethod::getBestSolution ()
{
	return population [0];
}