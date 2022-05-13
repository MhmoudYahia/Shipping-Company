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
int Truck::getDI() {
	return DI;
}
void Truck::updateDI() {
	HoursforGoingwithoutReturning = ceil(DisofFurthestCargo / Speed);
	DI = HoursforGoingwithoutReturning * 2 + LoadTimeofAllcargos ;
}
void Truck::decrementHoursleftforDelivery() {
	if(HoursforGoingwithoutReturning>0)HoursforGoingwithoutReturning--;
}
int Truck::getHoursleftforDelivery() {
	return HoursforGoingwithoutReturning;
}
void Truck::updatePriority() {

}
int Truck::getTimeleftforReturn() {
	return DI;
}
void Truck::decrementTimeleftforReturn() {
	if (DI > 0) DI--;
}
void Truck::setTimeforDelivery(Time X) {
	TimeforDelivery = X + HoursforGoingwithoutReturning;
}
void Truck::setTimeforReturn(Time X) {
	TimeforReturn = X + DI;
}
void Truck::setTimeforLoading(Time X) {
	TimeforLoading = X + LoadTimeofAllcargos; 
}
Time Truck::getTimeforDelivery() {
	return TimeforDelivery;
}
Time Truck::getTimeforReturn() {
	return TimeforReturn;
}
Time Truck::getTimeforLoading() {
	return TimeforLoading;
}
