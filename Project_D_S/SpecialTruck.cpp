#include "SpecialTruck.h"


SpecialTruck::SpecialTruck(int ID, int TC, int TS) :Truck(ID, TC, TS) {

}

void SpecialTruck::Print(UIClass* p)
{
	TruckCargos->PrintQ(p);
}
