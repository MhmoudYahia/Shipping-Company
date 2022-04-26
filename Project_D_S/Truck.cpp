#include "Truck.h"

int Truck::GetID()
{
	return ID;
}

//void Truck:: ChangeState(State S) {
//	TruckState = S;
	//CargoCount = 0;
//}
//Truck::Truck(int T) {
//	if (T > 0) TC = T;
//
//}
bool Truck::AddCargo(Cargo* C) {
	if (CargoCount == TC) {
		return false;
	}
	TruckCargos->enqueue(C);
	CargoCount++;
	return true;
}
bool Truck::RemoveCargo(Cargo* C) {
	if (CargoCount == 0) return false;
	TruckCargos->dequeue(C);
	return true;
}
void Truck::Print(UIClass * UI) {
	TruckCargos->PrintQ(UI);
}