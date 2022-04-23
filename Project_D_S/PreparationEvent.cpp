#include "PreparationEvent.h"


PreparationEvent::PreparationEvent(char typ, int dist, int lt, int cost, Time ET,int ID):Event(ET,ID) {
	setType(typ);
	setDistance(dist);
	setLoadTime(lt);
	setCost(cost);
}
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

Cargo * PreparationEvent::Execute()
{
	Cargo *  Cargoptr = new Cargo();
	return Cargoptr;
}
