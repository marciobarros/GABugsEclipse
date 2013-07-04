#include "StdAfx.h"
#include "Bug.h"

Bug::Bug(int index, int classIndex, int bugId, int priority, std::string product, std::string component, int effortTime)
{
	this->index = index;
	this->classIndex = classIndex;
	this->bugId = bugId;
	this->priority = priority;
	this->product = product;
	this->component = component;
	this->effortTime = effortTime;
	this->smithRatio = effortTime;
	this->smithRatio = (smithRatio / (MAX_BUG_PRIORITY - priority + 1));
}

Bug::~Bug(void)
{
}

int Bug::getIndex () 
{
	return index;
}

int Bug::getClassIndex ()
{
	return classIndex;
}

int Bug::getBugId (void)
{
	return this->bugId;
}

const char *Bug::getComponent (void)
{
	return this->component.c_str();
}

const char *Bug::getProduct (void)
{
	return this->product.c_str();
}

int Bug::getPriority (void)
{
	return this->priority;
}

int Bug::getEffortTime (void) 
{
	return this->effortTime;
}

double Bug::calculateSmithRatio ()
{
	return smithRatio;
}