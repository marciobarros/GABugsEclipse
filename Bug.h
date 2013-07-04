#pragma once

#ifndef BUG_H
#define BUG_H

#define MIN_BUG_PRIORITY 1
#define MAX_BUG_PRIORITY 5

class Bug
{
	private:
	int index;
	int classIndex;
	int bugId;
	int priority;
	std::string product;
	std::string component;
	int effortTime;
	double smithRatio;

	public:
	Bug(int index, int classIndex, int bugId, int priority, std::string product, std::string component, int effortTime);
	~Bug(void);
	int getBugId (void);
	int getPriority (void);
	const char *getComponent (void);
	const char *getProduct (void);
	int getEffortTime (void);
	double calculateSmithRatio ();
	int getIndex ();
	int getClassIndex ();
};

#endif