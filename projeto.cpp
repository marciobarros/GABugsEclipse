// projeto.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "random.h"
#include "historicaldata.h"
#include "RandonKeyMethod.h"
#include "LocalSearch.h"
#include "Chromosome.h"
#include <time.h>
#include <string>
#include <cstdlib> 

using namespace std;

void printSchedule(Chromosome *solution, char *type, int cycle, int populationSize, int numberOfSteps, int numberOfBugs)
{
	char sFileName [256];
	sprintf_s (sFileName, ".\\schedules\\SCH%s_%d_%d_%d_%02d.txt", type, populationSize, numberOfSteps, numberOfBugs, cycle);

	FILE *fileResults;
	fopen_s (&fileResults, sFileName, "wt");

	int numDevelopers = 0;
	Schedule *schedule = solution->getSchedule ();

	for (int i=0; i < schedule->getNumberOfDevelopers (); i++)
	{
		Developer *developer = schedule->getDeveloper (i);

		for (int j=0; j < developer->getNumberOfBugs(); j++)
		{
			std::string name = developer->getName ();
			Bug *bug = developer->getBug (j);
			int bugId = bug->getBugId ();
			int effort = bug->getEffortTime();
			int priority = bug->getPriority ();
			fprintf (fileResults, "%s;%d;%d;%d\n", name.c_str (), bugId, effort, priority);
		}
	}

	fclose(fileResults);
}

void runGeneticAlgorithm(FILE *fileResults, HistoricalData *fileReader, int populationSize, int numberOfSteps, int cycle)
{
	time_t start = time (NULL);
	RandomKeyMethod *method = new RandomKeyMethod (fileReader, populationSize);

	for (int i=0; i < numberOfSteps; i++)
	{
		printf ("GA Bugs %d - Cycle %d - Step %d       \r", fileReader->openBugList.size(), cycle, i);
		method->reproduct ();
	}

	Chromosome *bestSolution = method->getBestSolution();
	time_t finish = time (NULL);
	int diff = (int) (finish - start);

	printSchedule(bestSolution, "GA", cycle, populationSize, numberOfSteps, fileReader->openBugList.size());
	fprintf(fileResults, "Cycle %d; Time = %d; Cost = %.0f; Makespan = %d\n", cycle, diff, bestSolution->getCost(), bestSolution->getSchedule()->calculateMakespan());
	fflush(fileResults);
}

void runLocalSearch(FILE *fileResults, HistoricalData *fileReader, int populationSize, int numberOfSteps, int cycle)
{	
	printf ("LS Bugs %d - Cycle %d      \r", fileReader->openBugList.size(), cycle);
	int maxEvaluations = (int) (numberOfSteps * populationSize * (1 - TOPMOST_PERCENTIL));

	time_t start = time (NULL);
	LocalSearch *method = new LocalSearch(fileReader, maxEvaluations);
	Chromosome *bestSolution = method->run();

	time_t finish = time (NULL);
	int diff = (int) (finish - start);

	printSchedule(bestSolution, "LS", cycle, populationSize, numberOfSteps, fileReader->openBugList.size());
	fprintf(fileResults, "Cycle %d; Time = %d; Cost = %.0f; Makespan = %d\n", cycle, diff, bestSolution->getCost(), bestSolution->getSchedule()->calculateMakespan());
	fflush(fileResults);
}

int main(int argc, char* argv[])
{	
	int numberBugs = atoi (argv[1]);
	int populationSize = atoi (argv[2]);
	int cycles = atoi (argv[3]);
	char *type = argv[4];
	int numberOfSteps = 200;
	srand((unsigned)time(0));
	
	HistoricalData fileReader;
	fileReader.setNumberBugs (numberBugs);
	fileReader.load ();

	char sFileName [256];
	FILE *fileResults;
	sprintf_s (sFileName, ".\\resultados_%s_%d_%d_%d.txt", type, populationSize, numberOfSteps, numberBugs);
	fopen_s (&fileResults, sFileName, "wt");

	Schedule *scheduleDefault = fileReader.getSchedule ();
	fprintf (fileResults, "Actual Cost = %.0f\n", scheduleDefault->calculateCost (false));
	
	for (int i = 0; i < cycles; i++)
	{
		if (_stricmp(type, "GA") == 0)
			runGeneticAlgorithm(fileResults, &fileReader, populationSize, numberOfSteps, i);

		if (_stricmp(type, "LS") == 0)
			runLocalSearch(fileResults, &fileReader, populationSize, numberOfSteps, i);
	}

	fclose (fileResults);
	return 0;
}