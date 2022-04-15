#include "PreparationEvent.h"



void PreparationEvent::setType(char t)
{
	this->TYP = t;
}

void PreparationEvent::setDistance(int d)
{
	this->DIST = d;
}

void PreparationEvent::setLoadTime(int lt)
{
	this->LT = lt;
}

void PreparationEvent::setCost(int c)
{
	this->Cost = c;
}

char PreparationEvent::getType()
{
	return this->TYP;
}

int PreparationEvent::getDistance()
{
	return this->DIST;
}

int PreparationEvent::getLoadTime()
{
	return this->LT;
}

int PreparationEvent::getCost()
{
	return this->Cost;
}

void PreparationEvent::Execute()
{
	Cargo c;
	c.SetCost(this->getCost());
	c.SetDdes(this->getDistance());
	c.SetID(this->getID());
	c.SetLT(this->getLoadTime());
	c.setPT((this->getEventTime()).first, (this->getEventTime()).second);
}
