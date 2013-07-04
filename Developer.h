#pragma once
#include "stdafx.h"
#include "Bug.h"
#include <vector>

class Developer
{
	private:
	int index;
	std::string name;
	std::string email;
	std::vector <Bug*> bugList;

	private:
	void quicksortBugs (int l, int r);

	public:
	Developer(int index, std::string name, std::string email);
	~Developer(void);
	const char *getName (void);
	const char *getEmail (void);
	int getIndex (void);
	void addBug (Bug *bug);
	int getNumberOfBugs (void);
	Bug *getBug (int index);
	void removeBug (int index);
	double calculateCost (bool sort);
	int calculateMakespan ();
	void sortBugs ();
};