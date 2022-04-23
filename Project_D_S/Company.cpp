#include "Company.h"
#include"VIPCargo.h"
#include "SpecialCargo.h"
#include "NormalCargo.h"



void Company::LoadCargos() {
	Cargo* Cargoptr;
	WaitingCargos.peak(Cargoptr);
	bool Assigned = false;
	while (Cargoptr)
	{
		Assigned = false;
		Cargo* VIPCargoptr = dynamic_cast<VIPCargo*>( Cargoptr);
		Cargo* NormalCargoptr = dynamic_cast<NormalCargo*>(Cargoptr);
		Cargo* SpecialCargoptr = dynamic_cast<SpecialCargo*>(Cargoptr);
		if (VIPCargoptr) {
			Truck* Truckptr;
			VIPTrucks.peak(Truckptr);
			if (Truckptr) {
				VIPTrucks.dequeue(Truckptr);
				Truckptr->AddCargo(Cargoptr);
				Assigned = true;
			}
		}
		else if (SpecialCargoptr) {
			Truck* Truckptr;
			SpecialTrucks.peak(Truckptr);
			if (Truckptr) {
				SpecialTrucks.dequeue(Truckptr);
				Truckptr->AddCargo(Cargoptr);
				Assigned = true;
			}
		}
		else {
			Truck* Truckptr;
			NormalTrucks.peak(Truckptr);
			if (Truckptr) {
				NormalTrucks.dequeue(Truckptr);
				Truckptr->AddCargo(Cargoptr);
				Assigned = true;
			}
			else {
				VIPTrucks.peak(Truckptr);
				if (Truckptr) {
					VIPTrucks.dequeue(Truckptr);
					Truckptr->AddCargo(Cargoptr);
					Assigned = true;
				}
			}
		}
		if (Assigned) {
			WaitingCargos.dequeue(Cargoptr);
			WaitingCargos.peak(Cargoptr);
		}
		else {
			Cargoptr->IncrementWaitingHours();
		}

	}
}

void Company::IncrementHour()
{
	bool bo;
	PromotionEvent* ptr=nullptr;
	bo=this->PromotionEvents.peak(ptr);
	if(bo)
		while (this->getcurtime() <= ptr->getEventTime())
		{
			
			this->setcurtime(this->getcurtime() + 1);
		}
}

void Company::setcurtime(Time time)
{
	this->CurrentTime.sethour(time.gethour());
	this->CurrentTime.setDAY(time.getDAY());
}

Time Company::getcurtime()
{
	return this->CurrentTime;
}
