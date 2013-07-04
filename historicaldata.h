#pragma once
#include "Bug.h"
#include "Developer.h"
#include "Schedule.h"
#include <vector>

class BugHistoricalData
{
	private:
	int bugClass;
	int developerIndex;
	double percentile;
	
	public:
	BugHistoricalData(int bugClass, int developerIndex, double percentile);
	double getPercentile (void);
	int getBugClass (void);
	int getDeveloperIndex (void);
};

class HistoricalData
{
	public:
	std::vector <BugHistoricalData*> bugsHistoricalData;
	std::vector <Bug*> openBugList;
	std::vector <Developer*> developerList;
	Schedule *scheduleDefault;

	private:
	int getBugPriority (std::string priority);
	int numberBugs;
	void loadBugs (void);
	void loadDevelopers (void);
	void loadSchedule (void);
	void loadAssignments (void);
	void addBug (Bug* bug);
	Developer *getDeveloper (const char *developerName);
	Bug *getBug (int bugId);

	public:
	void load (void);
	void setNumberBugs (int bugs);
	int HistoricalData::getDeveloperIndex (int bugClass, double key);
	Schedule *getSchedule ();
	HistoricalData(void);
	~HistoricalData(void);
};