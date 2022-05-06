#pragma once
#include "Truck.h"
class SpecialTruck :
	public Truck
{
public:

	SpecialTruck(int ID, int TC, int TS);
	void Print(UIClass* p);
};

