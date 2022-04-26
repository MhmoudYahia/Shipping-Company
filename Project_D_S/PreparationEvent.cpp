#include "PreparationEvent.h"
#include "Company.h"

PreparationEvent::PreparationEvent(char typ, int dist, int lt, int cost, Time ET,int ID,Company * C):Event(ET,ID, C) {
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

void PreparationEvent::Execute()
{
	cout << "Event Executed \n";
	int D = getEventTime().getDAY();
	int H = getEventTime().gethour();
	int ID = getID();
	Cargo* Cargoptr = new Cargo(Cost, LT, DIST, ID, H, D);
	NormalCargo* NC = new NormalCargo(Cost, LT, DIST, ID, H, D);
	VIPCargo* VC = new VIPCargo(Cost, LT, DIST, ID, H, D);
	SpecialCargo* SC = new SpecialCargo(Cost, LT, DIST, ID, H, D);

	switch (TYP)
	{
	case 'N':
		Cptr->AddCargotoWaiting(NC);
		break;
	case 'V':
		Cptr->AddCargotoWaiting(VC);
		break;
	case 'S':
		Cptr->AddCargotoWaiting(SC);
		break;
	default:
		Cptr->AddCargotoWaiting(Cargoptr);
		break;
	}
}
