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
public:
	PreparationEvent(char, int, int, int);
	void setType(char t);
	void setDistance(int d);
	void setLoadTime(int lt);
	void setCost(int c);
	char getType();
	int getDistance();
	int getLoadTime();
	int getCost();
	void virtual Execute();
};

