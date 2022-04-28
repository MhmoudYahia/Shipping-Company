#include "Company.h"
#include"VIPCargo.h"
#include "SpecialCargo.h"
#include "NormalCargo.h"
#include <chrono>
#include <thread>
#include "Event.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Company::Company()
{
	pUI = new UIClass();
	CurrentTime.sethour(1);
	CurrentTime.setDAY(1);
}

void Company::LoadCargos() {
	/*Cargo* Cargoptr;
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

	}*/
}

//void Company::IncrementHour()
//{
//	bool bo;
//	PromotionEvent* ptr=nullptr;
//	bo=this->PromotionEvents.peak(ptr);
//	if(bo)
//		while (this->getcurtime() <= ptr->getEventTime())
//		{
//			
//			this->setcurtime(this->getcurtime() + 1);
//		}
//}

void Company::setcurtime(Time time)
{
	this->CurrentTime.sethour(time.gethour());
	this->CurrentTime.setDAY(time.getDAY());
}

Time Company::getcurtime()
{
	return this->CurrentTime;
}

void Company::StepbyStepSimulation()
{
	int cnt = 10;
	while (cnt++) {
		ExecuteEvents();
		PrintConsole();
		Sleep(1500);
		++CurrentTime;
		//to move cago from waiting to delivered every 5 times
		if (cnt % 5 == 0) {
			Cargo* Cptr;
			WaitingCargos.dequeue(Cptr);
			this->DeliveredCargos.enqueue(Cptr);
		}
	}
}
void Company::PrintConsole() {
	pUI->PrintCurrentTime(this->CurrentTime);
	pUI->printWaitingCargos(this->WaitingCargos);
	pUI->PrintLine();
	pUI->PrintLoadingTrucks(this->LoadingTrucks);
	pUI->PrintLine();
	pUI->PrintEmptytrucks(this->EmptyTrucks);
	pUI->PrintLine();
	pUI->PrintMovingCargos(this->MovingCargos);
	pUI->PrintLine();
	pUI->PrintIn_CheckupTrucks(this->InCheckupTrucks);
	pUI->PrintLine();
	pUI->PrintDeliveredCargo(this->DeliveredCargos);
	pUI->PrintLine();
}
void Company::InteractiveSimulation() {
	int cnt = 10;
	while (cnt++) {
		ExecuteEvents();
		PrintConsole();
		++CurrentTime;
		pUI->getKey();
		int v = 5;
		//to move cago from waiting to delivered every 5 times
		if (cnt % 5 == 0) {               
			Cargo* Cptr;
			WaitingCargos.dequeue(Cptr);
			this->DeliveredCargos.enqueue(Cptr);
		}
	}
}
void Company::GeneralSimulate() {
	switch (pUI->SelectMode()) {
	case interactive:
	{	
		InteractiveSimulation();
		break;	
	}
	case step_by_step: {
		StepbyStepSimulation();
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
	Lfile.open("Text.txt");      //start from here to read 			 
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
		case 'R': {
			char TYP;
			int H, D;
			int ID;
			int DIST;
			double LT;
			int Cost;
			char colon;
			Lfile >> TYP >> D >> colon >> H >> ID >> DIST >> LT >> Cost;
			Time ET(D, H);
			Cargo* C;
			PreparationEvent* PE = new PreparationEvent(TYP, DIST, LT, Cost, ET, ID, this);
			Event* E = PE;
			double priority = -((D - 1) * 24 + H);
			EventsPQ.enqueue(E, priority);
			break; }
		case 'X': {
			int H, D;
			int ID;
			char colon;
			Lfile >> D >> colon >> H >> ID;
			Time ET(D, H);
			CancellationEvent* CE = new CancellationEvent(ET, ID, this);
			Event* E = CE;
			double priority = -((D - 1) * 24 + H);
			EventsPQ.enqueue(E, priority);
			break;
		}
		case 'P': {
			int H, D;
			int ID;
			char colon;
			int ExtraMoney;
			Lfile >> D >> colon >> H >> ID >> ExtraMoney;
			Time ET(D, H);
			PromotionEvent* PRE = new PromotionEvent(ET, ID, ExtraMoney, this );
			double priority = -((D - 1) * 24 + H);
			Event* E = PRE;
			EventsPQ.enqueue(E, priority);
			break;
		}
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
	EventsPQ.peak(Eptr);
	while (EventsPQ.GetCount()>0){
		cout << "Current EventCount: " << EventsPQ.GetCount() << endl;
		EventsPQ.dequeue(Eptr);
		Eptr->Execute();
	}
}
void Company::AddCargotoWaiting(Cargo* C) {
	WaitingCargos.enqueue(C,0);
}
bool Company::UpdatetoVIP(int ID) {
	Cargo* C = NULL;
	Cargo* Search = NULL;
	WaitingCargos.peak(C);
	PriorityQueue<Cargo* > temp;
	while(WaitingCargos.GetCount()>0) {
		if (C->GetID() == ID) {
			Search = C;
		}
		else temp.enqueue(C, C->Getpriority());
		WaitingCargos.dequeue(C);
		WaitingCargos.peak(C);
	}
	temp.peak(C);
	while (temp.GetCount()>0) {
		WaitingCargos.enqueue(C, C->Getpriority());
		temp.dequeue(C);
		temp.peak(C);
	}
	if (Search) {
		int id = Search->GetID();
		int h = Search->getPT().gethour();
		int d = Search->getPT().getDAY();
		int lt = Search->getLT();
	//	double p = Search->Getpriority();  //M
		double dis = Search->getDdes();
		double c = Search->getCost();
		VIPCargo* VC = new VIPCargo(id/*, p*/, d, h, lt, c, dis);
		WaitingCargos.enqueue(VC, VC->Getpriority());
		return true;
	}
	return false;
}
void Company::PrintEvents() {
	Event* E;
	int cnt = 0;
	EventsPQ.peak(E);
	while (EventsPQ.GetCount()>0) {
		cnt++;
		if (dynamic_cast<PromotionEvent*> (E)) cout << "PRE";
		if (dynamic_cast<CancellationEvent*> (E)) cout << "CE";
		if (dynamic_cast<PreparationEvent*> (E)) cout << "PE";
		cout << cnt << endl;
		EventsPQ.dequeue(E);
		//EventsPQ.peak(E);
	}
	cout << N << " " << S << " " << V;
}

void Company::cancellID(int id)
{
	Queue<Cargo*>Q;
	Cargo* Cptr;
	while (WaitingCargos.dequeue(Cptr)) {
		if (Cptr->GetID() != id) {
			Q.enqueue(Cptr);
		}
	}
	while (Q.dequeue(Cptr))
		WaitingCargos.enqueue(Cptr, Cptr->Getpriority());
}
NormalCargo* Company::GetNormalCargo(int id) {
	Queue<Cargo*>Q;
	NormalCargo* temp=nullptr;
	Cargo* Cptr;
	while (WaitingCargos.dequeue(Cptr)) {
		Q.enqueue(Cptr);
		if (Cptr->GetID() == id) {
			temp=dynamic_cast<NormalCargo*> (Cptr);
		}
	}
	while (Q.dequeue(Cptr))
		WaitingCargos.enqueue(Cptr, Cptr->Getpriority());
	return temp;
}