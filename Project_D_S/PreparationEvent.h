#pragma once
#include"Event.h"
#include"Cargo.h"
#include"NormalCargo.h"
class PreparationEvent :public Event
{
	char TYP;
	int DIST;
	int LT;
	int Cost;
	Cargo* Cargoptr;
public:
	PreparationEvent(char typ,	int dist, int lt, int cost, Time ET, int ID, Cargo * C);
	void setType(char t);
	void setDistance(int d);
	void setLoadTime(int lt);
	void setCost(int c);
	char getType();
	int getDistance();
	int getLoadTime();
	int getCost();
	void setCargo(Cargo*);
	virtual void  Execute();
};

