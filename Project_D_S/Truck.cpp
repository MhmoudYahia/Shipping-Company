#include "Truck.h"

int Truck::GetID()
{
	return ID;
}

Truck::Truck(int ID, int TC, int TS) {
	this->ID = ID;
	this->TC = TC;
	this->Speed = TS;
	TruckCargos = new Queue<Cargo*>;
	JourneyCount = 0;
}
bool Truck::AddCargo(Cargo* C) {
	if (CargoCount == TC) {
		return false;
	}
	if (!C) return false;
	TruckCargos->enqueue(C);
	CargoCount++;
	return true;
}
bool Truck::RemoveCargo(Cargo* C) {
	if (CargoCount == 0) return false;
	TruckCargos->dequeue(C);
	return true;
}
//void Truck::Print(UIClass * UI) {
//	UI->Print(this);
//}
bool Truck::isFull() {
	return (CargoCount == TC);
}
void Truck::setSpeed(double s) {
	if(s>0)Speed = s;
}
void Truck::Print(UIClass * UI) {
	TruckCargos->PrintQ(UI);
}
void Truck::incrementJC() {
	JourneyCount++;
}
void Truck::resetJC() {
	JourneyCount = 0;
}
int Truck::getJC() {
	return JourneyCount;
}