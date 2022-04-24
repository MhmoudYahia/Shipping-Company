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
	bool simulate = true;
	while (simulate) {
		ExecuteEvents();
		PrintConsole();
		CurrentTime++;
	}
}
void Company::PrintConsole() {
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
}
void Company::SimulateStepbyStep() {
	while (true) {
		ExecuteEvents();
		PrintConsole();
		CurrentTime++;
		pUI->getKey();
	}
}
void Company::GeneralSimulate() {
	switch (pUI->SelectMode()) {
	case interactive:
	{	
		SimulateAutomatic();
		break;	
	}
	case step_by_step: {
		SimulateStepbyStep();
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
			double priority = -((D - 1) * 24 + H);
			Events.enqueue(PE, priority);
			break;
		case 'X':
			int H, D;
			int ID;
			char colon;
			Lfile  >> D >> colon >> H >> ID ;
			Time ET(D, H);
			CancellationEvent *CE = new CancellationEvent(ET,ID);
			double priority = -((D - 1) * 24 + H);
			Events.enqueue(CE, priority);
			break;
		case 'P':
			int H, D;
			int ID;
			char colon;
			int ExtraMoney;
			Lfile >> D >> colon >> H >> ID>>ExtraMoney;
			Time ET(D, H);
			PromotionEvent* PRE = new PromotionEvent(ET, ID,ExtraMoney);
			double priority = -((D - 1) * 24 + H);
			Events.enqueue(PRE,priority);	
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
void Company:: ExecuteEvents() {
	if (isClosed()) {
		return;
	}
	Event* Eptr;
	Events.peak(Eptr);
	PreparationEvent* PE = dynamic_cast <PreparationEvent*> (Eptr);
	while (Eptr && Eptr->getEventTime() == CurrentTime) {
		PreparationEvent* PE = dynamic_cast <PreparationEvent*> (Eptr);
		PromotionEvent* PROE = dynamic_cast <PromotionEvent*> (Eptr);
			Eptr->Execute();
			if (PE) {
				Cargo* C = PE->getCargo();
				WaitingCargos.enqueue(C,C->Getpriority());
			}
			if (PROE) {
				NormalCargo* NC = PROE->getNormalCargo();
				UpdatetoVIP(NC->GetID());
			}
			Events.dequeue(Eptr);
			Events.peak(Eptr);
	}
}
void Company::AddCargotoWaiting(Cargo* C) {
	WaitingCargos.enqueue(C, C->Getpriority());
}
bool Company::UpdatetoVIP(int ID) {
	Cargo* C = NULL;
	Cargo* Search = NULL;
	WaitingCargos.peak(C);
	PriorityQueue<Cargo* > temp;
	while(C ) {
		if (C->GetID() == ID) {
			Search = C;
		}
		else temp.enqueue(C, C->Getpriority());
		WaitingCargos.dequeue(C);
		WaitingCargos.peak(C);
	}
	temp.peak(C);
	while (C) {
		WaitingCargos.enqueue(C, C->Getpriority());
		temp.dequeue(C);
		temp.peak(C);
	}
	if (Search) {
		int id = Search->GetID();
		int h = Search->getPT().gethour();
		int d = Search->getPT().getDAY();
		int lt = Search->getLT();
		double p = Search->Getpriority();
		double dis = Search->getDdes();
		double c = Search->getCost();
		VIPCargo* VC = new VIPCargo(id, p, d, h, lt, c, dis);
		WaitingCargos.enqueue(VC, VC->Getpriority());
		return true;
	}
	return false;
}