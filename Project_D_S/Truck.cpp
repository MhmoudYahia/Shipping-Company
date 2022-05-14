#include "Truck.h"
#include "Company.h"

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
	C->setDel_H(Speed);
	C->set_TrkId(this->GetID());
	CargoCount++;
	return true;
}
int Truck::GetCountOFCargosInTRK() {
	return TruckCargos->GetCount();
}
void Truck::set_ActiveTime()
{
	this->ActiveTime = this->ActiveTime + ceil(DisofFurthestCargo / Speed) + LoadTimeofAllcargos;
}

Time Truck::get_ActiveTime()
{
	return this->ActiveTime;
}

int Truck::Truck_utilization(int T)
{
	if (JourneyCount == 0)
		return 0;
	else
		return (this->CargoCount / (this->TC * this->JourneyCount)*((this->ActiveTime.gethour() + 24 *this->ActiveTime.getDAY()) /T));
}

bool Truck::RemoveCargo(Cargo* &C) {
	C = nullptr;
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
void Truck::ResetDeliveryTime() {
	TimeforDelivery.setDAY(0);
	TimeforDelivery.sethour(0);
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
	Priority = -(TimeforDelivery.getDAY() * 24 + TimeforDelivery.gethour());
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
int Truck::getPriority() {
	return Priority;
}
Cargo* Truck::GetFurthestCargo() {
	Queue<Cargo*>q;
	return nullptr;
}
Queue<Cargo* > Truck::getDelivered(Time T) {
	Queue<Cargo* > Q;
	Queue<Cargo*> temp;
	Cargo* C;
	while (TruckCargos->GetCount() > 0) {
		TruckCargos->dequeue(C);
		if (C->getDel_T() == T) {
			Q.enqueue(C);
		}
		else {
			temp.enqueue(C);
		}
	}
	while (temp.GetCount() > 0) {
		temp.dequeue(C);
		TruckCargos->enqueue(C);
	}
	cout << Q.GetCount() << "xxxxxxxxxxxxx";
	 return Q;
}
void Truck::updateCargosDT() {
	Queue<Cargo*> X; Cargo* C = nullptr;
	while (TruckCargos && TruckCargos->dequeue(C)) {
		C->setDel_T(TimeforLoading);
		X.enqueue(C);
	}
	C = nullptr;
	while (X.dequeue(C)&&C) TruckCargos->enqueue(C);
}