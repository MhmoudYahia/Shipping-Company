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
	CheckforCargosExceededMaxW();
	AssignExceeded();
	AssignVIP();
	AssignSpecial();
	AssignNormal();
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
		////to move cago from waiting to delivered every 5 times
		//if (cnt % 5 == 0 &&WaitingCargos.GetCount()>0) {
		//	Cargo* Cptr;
		//	WaitingCargos.dequeue(Cptr);
		//	this->DeliveredCargos.enqueue(Cptr);
		//}
	}
}
void Company::PrintConsole() {
	pUI->PrintCurrentTime(this->CurrentTime);
	pUI->PrintWaitingCargos(this);
	pUI->PrintLine();
	pUI->PrintLoadingTrucks(this->LoadingTrucks);
	pUI->PrintLine();
	//pUI->PrintEmptytrucks(this->EmptyTrucks);
	pUI->PrintLine();
	pUI->PrintMovingCargos(this->MovingCargos);
	pUI->PrintLine();
	pUI->PrintIn_CheckupTrucks(this->InCheckupTrucks);
	pUI->PrintLine();
	pUI->PrintDeliveredCargo(this);
	pUI->PrintLine();
}
void Company::InteractiveSimulation() {
	int cnt = 10;
	while (cnt++) {
		ExecuteEvents();
		PrintConsole();
		++CurrentTime;
		pUI->getKey();
		//int v = 5;
		/*if (cnt % 5 == 0 && WaitingCargos.GetCount() > 0) {
			Cargo* Cptr;
			WaitingCargos.dequeue(Cptr);
			this->DeliveredCargos.enqueue(Cptr);
		}*/
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
	//if (isClosed()) {
	//	return;
	//}
	Event* Eptr;
	EventsPQ.peak(Eptr);
	if (!Eptr ||EventsPQ.GetCount()==0) return;
	Time X = Eptr->getEventTime();
	if (!(X==CurrentTime)) return;
	while (EventsPQ.GetCount()>0 &&  Eptr->getEventTime()== CurrentTime)
		{
		cout << "Current EventCount: " << EventsPQ.GetCount() << endl;
		EventsPQ.dequeue(Eptr);
		Eptr->Execute();
		EventsPQ.peak(Eptr);
	}
}
void Company::AddCargotoVIPWaiting(VIPCargo* C) {
	WaitingVIPCargos.enqueue(C, C->Getpriority());
}
void Company::AddCargotoNormalWaiting(Cargo* n) {
	WaitingNormalCargos.InsertEnd(n);
}
void Company::AddCargotoSpWaiting(SpecialCargo* n) {
	WaitingSpecialCargos.enqueue(n);
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
		cout << "ID: " << E->getID() << endl;
		//EventsPQ.peak(E);
	}
	cout << N << " " << S << " " << V;
}

void Company::CancellationID(int id)
{
	WaitingNormalCargos.Remove(id);
}
NormalCargo* Company::GetNormalCargo(int id) {
	return dynamic_cast<NormalCargo*>(WaitingNormalCargos.PointerToNormalCRGO(id)->getitem());
}
void Company::printWaitingVIP(UIClass* pUI) {
	if (WaitingVIPCargos.GetCount() > 0) {
		pUI->openbraceforVIP();
		WaitingVIPCargos.PrintQ(pUI);
		pUI->closebraceforVIP();
	}
}
void Company::printWaitingNormal(UIClass* pUI) {
	if (WaitingNormalCargos.GetCount() > 0){
	   pUI->openbraceforNormal();
	   WaitingNormalCargos.PrintL(pUI);
	   pUI->closebraceforNormal();
    }
}
void Company::printWaitingSP(UIClass* pUI) {
	if (WaitingSpecialCargos.GetCount() > 0) {
		pUI->openbraceforSP();
		WaitingSpecialCargos.PrintQ(pUI);
		pUI->closebraceforSP();
	}
}
int Company::Getcountall_waiting() {
	return WaitingVIPCargos.GetCount() + WaitingNormalCargos.GetCount() + WaitingSpecialCargos.GetCount();
}

int Company::GetnumOfDeliv() {
	return DeliveredNormalCargo.GetCount()+DeliveredSpCargo.GetCount()+DeliveredVIPCargo.GetCount();
}
void Company::printDeliveredVIP(UIClass* pUI) {
	if (DeliveredVIPCargo.GetCount() > 0) {
		pUI->openbraceforVIP();
		DeliveredVIPCargo.PrintQ(pUI);
		pUI->closebraceforVIP();
	}
}
void Company::printDeliveredNormal(UIClass* pUI) {
	if (DeliveredNormalCargo.GetCount() > 0) {
		pUI->openbraceforNormal();
		DeliveredNormalCargo.PrintQ(pUI);
		pUI->closebraceforNormal();
	}
}
void Company::printDeliveredSP(UIClass* pUI) {
	if (DeliveredSpCargo.GetCount() > 0) {
		pUI->openbraceforSP();
		DeliveredSpCargo.PrintQ(pUI);
		pUI->closebraceforSP();
	}
}
//
//void Company::cancellID(int id)
//{
//	Queue<Cargo*>Q;
//	Cargo* Cptr;
//	while (WaitingCargos.dequeue(Cptr)) {
//		if (Cptr->GetID() != id) {
//			Q.enqueue(Cptr);
//		}
//	}
//	while (Q.dequeue(Cptr))
//		WaitingCargos.enqueue(Cptr, Cptr->Getpriority());
//}
//void Company::PrintDelivered(UIClass* pUI) {
//	if(Deli)
//	DeliveredCargos.PrintQ(pUI);
//}
	/*Queue<Cargo*>Q;
	NormalCargo* temp=nullptr;
	Cargo* Cptr;
	while (WaitingCargos.dequeue(Cptr)) {
		if (Cptr->GetID() == id) {
			temp=dynamic_cast<NormalCargo*> (Cptr);
		}
		else Q.enqueue(Cptr);
	}
	while (Q.dequeue(Cptr))
		WaitingCargos.enqueue(Cptr, Cptr->Getpriority());*/
	
		//bool Company::UpdatetoVIP(int ID) {                //notworking, see getnormalCargo func and its excute 
		//	Cargo* C = NULL;
		//	Cargo* Search = NULL;
		//	WaitingCargos.peak(C);
		//	PriorityQueue<Cargo* > temp;
		//	while(WaitingCargos.GetCount()>0) {
		//		if (C->GetID() == ID) {
		//			Search = C;
		//		}
		//		else temp.enqueue(C, C->Getpriority());
		//		WaitingCargos.dequeue(C);
		//		WaitingCargos.peak(C);
		//	}
		//	temp.peak(C);
		//	while (temp.GetCount()>0) {
		//		WaitingCargos.enqueue(C, C->Getpriority());
		//		temp.dequeue(C);
		//		temp.peak(C);
		//	}
		//	if (Search) {
		//		int id = Search->GetID();
		//		int h = Search->getPT().gethour();
		//		int d = Search->getPT().getDAY();
		//		int lt = Search->getLT();
		//	//	double p = Search->Getpriority();  //M
		//		double dis = Search->getDdes();
		//		double c = Search->getCost();
		//		VIPCargo* VC = new VIPCargo(id/*, p*/, d, h, lt, c, dis);
		//		WaitingCargos.enqueue(VC, VC->Getpriority());
		//		return true;
		//	}
		//	return false;
		//}
void Company::CheckforCargosExceededMaxW() {
	// Normal Check 
	Cargo* C = WaitingNormalCargos.Head()->getitem();
	while(C->GetWaitingHours() >= MaxW) {
		WaitingNormalCargos.DeleteFirst(C);
		NCargosExceededMaxW.enqueue(C);
		C = WaitingNormalCargos.Head()->getitem();
	}
	//Special Check 
	WaitingSpecialCargos.peak(C);
	while (C->GetWaitingHours() >= MaxW) {
		WaitingSpecialCargos.dequeue(C);
		SCargosExceededMaxW.enqueue(C);
		WaitingSpecialCargos.peak(C);
	}
	//VIP check 
	WaitingVIPCargos.peak(C);
	while (C->GetWaitingHours() >= MaxW) {
		WaitingVIPCargos.dequeue(C);
		VCargosExceededMaxW.enqueue(C);
		WaitingVIPCargos.peak(C);
	}

}
bool Company::AssignVIP() {
	Cargo* VC;
	if (VIPEmptyTrucks.GetCount() > 0 && V <= WaitingVIPCargos.GetCount()) {
		AssignVIPTruck(0);
		return true;
	}
	else if (NormalEmptyTrucks.GetCount() > 0 && N <= WaitingVIPCargos.GetCount()) {
		AssignNormalTruck(0);
		return true;
		
	}
	else if (SpecialEmptyTrucks.GetCount() > 0 && S <= WaitingVIPCargos.GetCount()) {
		AssignSpecialTruck(0);
		return true;
	}
	else {
		return false;
	}
}
bool Company::AssignSpecial() {
	Cargo* SC;
	if (SpecialEmptyTrucks.GetCount() > 0 && S <= WaitingVIPCargos.GetCount()) {
		AssignSpecialTruck(1);
		return true;
	}
	return false;
}
bool Company::AssignNormal() {
	Cargo* NC;
	if (NormalEmptyTrucks.GetCount() > 0 && N <= WaitingNormalCargos.GetCount()) {
		AssignNormalTruck(1);
		return true;
	}
	else if (VIPEmptyTrucks.GetCount() > 0 &&V <= WaitingNormalCargos.GetCount()) {
		AssignVIPTruck(1);
		return true;
	}
	return false;
}
void Company::AssignVIPTruck(int T) {
	Cargo* C;
		VIPTruck* VT;
		VIPEmptyTrucks.dequeue(VT);
		while (!VT->isFull()) {
			if (T == 0)WaitingVIPCargos.dequeue(C);
			else if(T==1) WaitingNormalCargos.DeleteFirst(C);
			else if (T == 2)VCargosExceededMaxW.dequeue(C);
			else if (T == 3)SCargosExceededMaxW.dequeue(C);
			if (!C) break;
			VT->AddCargo(C);
		}
		VIPEmptyTrucks.dequeue(VT);
		LoadingTrucks.enqueue(VT);
}
void Company::AssignNormalTruck(int T) {
	Cargo* C;
		NormalTruck* NT;
		NormalEmptyTrucks.dequeue(NT);
		while (!NT->isFull()) {
			if (T == 0)
				WaitingVIPCargos.dequeue(C);
			else if (T == 1)WaitingNormalCargos.DeleteFirst(C);
			else if (T == 2)VCargosExceededMaxW.dequeue(C);
			else if(T==3)NCargosExceededMaxW.dequeue(C);
			if (!C) break;
			NT->AddCargo(C);
		}
		NormalEmptyTrucks.dequeue(NT);
		LoadingTrucks.enqueue(NT);
}
void Company::AssignSpecialTruck(int T) {
	Cargo* C;
	SpecialTruck* ST;
	SpecialEmptyTrucks.dequeue(ST);
	while (!ST->isFull()) {
		if (T == 0) WaitingVIPCargos.dequeue(C);
		else if (T == 1)WaitingSpecialCargos.dequeue(C);
		else if (T == 2)VCargosExceededMaxW.dequeue(C);
		else if (T == 3)SCargosExceededMaxW.dequeue(C);
		if (!C) break;
		ST->AddCargo(C);
	}
	SpecialEmptyTrucks.dequeue(ST);
	LoadingTrucks.enqueue(ST);
}
void Company::AssignExceeded() {
	Cargo* Cargoptr;
	if (VCargosExceededMaxW.GetCount() > 0) {
		if (VIPEmptyTrucks.GetCount() > 0) {
			AssignVIPTruck(2);
		}
		else if (NormalEmptyTrucks.GetCount() > 0) {
			AssignNormalTruck(2);
		}
		else if (SpecialEmptyTrucks.GetCount() > 0) {
			AssignSpecialTruck(2);
		}
	}
	if (SCargosExceededMaxW.GetCount() > 0) {
		if (SpecialEmptyTrucks.GetCount() > 0) {
			AssignSpecialTruck(3);
		}
	}
	if (NCargosExceededMaxW.GetCount() > 0) {
		if (NormalEmptyTrucks.GetCount() > 0) {
			AssignNormalTruck(3);
		}
		else if (VIPEmptyTrucks.GetCount() > 0) {
			AssignVIPTruck(3);
		}
	}
}