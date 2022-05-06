#include "VIPTruck.h"


VIPTruck::VIPTruck(int ID, int TC, int TS) :Truck(ID, TC, TS) {

}

void VIPTruck::Print(UIClass* p)
{
	TruckCargos->PrintQ(p);
}
