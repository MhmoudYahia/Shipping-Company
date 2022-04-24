#include "Company.h"
#include"VIPCargo.h"
#include "SpecialCargo.h"
#include "NormalCargo.h"
#include <chrono>
#include <thread>



Company::Company()
{
	pUI = new UIClass();
}

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

void Company::SimulateAutomatic()
{
		pUI->PrintCurrentTime(this->CurrentTime);
		pUI->printWaitingCargos(&this->WaitingCargos);
		pUI->PrintLine();
		pUI->PrintLoadingTrucks(&this->LoadingTrucks);
		pUI->PrintLine();
		pUI->PrintEmptytrucks(&this->EmptyTrucks);
		pUI->PrintLine();
		pUI->PrintMovingCargos(&this->MovingCargos);
		pUI->PrintLine();
		pUI->PrintIn_CheckupTrucks(&this->InCheckupTrucks);
		pUI->PrintLine();
		pUI->PrintDeliveredCargo(&this->DeliveredCargos);
		IncrementHour();
}
void Company::GeneralSimulate() {
	switch (pUI->SelectMode()) {
	case interactive:
	{	
		SimulateAutomatic();
		pUI->getKey();
		break;
	}
	case step_by_step: {
		SimulateAutomatic();
		break;
	}
	case silent:
	{
		pUI->PrintSilentMode();
		break;
	}
	}
}

void Company::Loading_File()
{
	ifstream Lfile;
	Lfile.open("CompFile.txt");      //start from here to read 
									 
	Lfile >> N >> S >> V;
	Lfile >> NTruckSpeed >> STruckSpeed >> VTruckSpeed;
	Lfile >> NTruckCapacity >> STruckCapacity >> VTruckCapacity;
	Lfile >> JourneyCount>> NTruckCheckupDuration>>STruckCheckupDuration>>VTruckChekcupDuration;
	Lfile >> AutoP >> MaxW;
	Lfile >> EventCount;
	char E;
	for (int i = 0; i < EventCount; i++)
	{
		Lfile >> E;
		switch (E)
		{
		case 'R':
			char TYP;
			int H, D;
			int ID;
			int DIST;
			int LT;
			int Cost;
			char colon;
			Lfile >> TYP >> D>>colon>>H >> ID >> DIST >> LT >> Cost;
			Time ET(D,H);
			Cargo* C;
			PreparationEvent* PE = new PreparationEvent(TYP, DIST, LT, Cost, ET,ID,C);
			PreparationEvents.enqueue(PE);
			WaitingCargos.enqueue(C, 0 );
			break;
		case 'X':
			int H, D;
			int ID;
			char colon;
			Lfile  >> D >> colon >> H >> ID ;
			Time ET(D, H);
			CancellationEvent *CE = new CancellationEvent(ET,ID);
			CancellationEvents.enqueue(CE);
			break;
		case 'P':
			int H, D;
			int ID;
			char colon;
			int ExtraMoney;
			Lfile >> D >> colon >> H >> ID>>ExtraMoney;
			Time ET(D, H);
			PromotionEvent* PRE = new PromotionEvent(ET, ID,ExtraMoney);
			PromotionEvents.enqueue(PRE);
			break;
		default:
			break;
		}
	}
	Lfile.close();
}
void Company::setMaxW(int M) {
	if (M > 0) MaxW = M;
}
bool Company::isClosed() {
	int H = CurrentTime.gethour();
	if (H >= 5 && H <= 23) return false;
	return true;
}
void Company::OutputFile() {
	ofstream Lfile;
	Lfile.open("Output.txt");
	Lfile << "CDT\t\tID\t\tWT\t\tTID\n";
}