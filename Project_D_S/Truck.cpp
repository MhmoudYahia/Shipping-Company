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
	DisofFurthestCargo = 0;
	LoadTimeofAllcargos = 0;
}

bool Truck::AddCargo(Cargo* C) {
	if (CargoCount == TC) {
		return false;
	}
	if (!C) return false;
	DisofFurthestCargo = max(DisofFurthestCargo, C->getDis());
	LoadTimeofAllcargos += C->getLT();
	TruckCargos->enqueue(C);
	C->set_TrkId(this->GetID());
	CargoCount++;
	return true;
}

void Truck::set_ActiveTime()
{
	this->ActiveTime = this->ActiveTime + ceil(DisofFurthestCargo / Speed) + LoadTimeofAllcargos;
}

Time Truck::get_ActiveTime()
{
	return this->ActiveTime;
}

int Truck::Truck_utilization()
{
	if (JourneyCount == 0)
		return 0;
	else
		return (this->CargoCount / (this->TC * this->JourneyCount)*((this->ActiveTime.gethour() + 24 *this->ActiveTime.getDAY()) / /*PUT HERE total Simulation time YA AHMED ^ _ ^ /*/));
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
int Truck::getDI() {
	return DI;
}
void Truck::updateDI() {
	TimeforGoingwithoutReturning = ceil(DisofFurthestCargo / Speed);
	DI = TimeforGoingwithoutReturning * 2 + LoadTimeofAllcargos ;
}
void Truck::decrementTimeleftforDelivery() {
	if(TimeforGoingwithoutReturning>0)TimeforGoingwithoutReturning--;
}
int Truck::getTimeleftforDelivery() {
	return TimeforGoingwithoutReturning;
}