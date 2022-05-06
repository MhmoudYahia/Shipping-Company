#include "NormalTruck.h"


NormalTruck::NormalTruck(int ID, int TC, int TS) :Truck(ID, TC, TS) {

}

void NormalTruck::Print(UIClass* p)
{
	TruckCargos->PrintQ(p);
}
