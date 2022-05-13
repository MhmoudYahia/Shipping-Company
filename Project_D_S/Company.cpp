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
	TruckCount = 0;
	this->NumberOfAutoPromotedCargos = 0;		//ismail
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
		CheckforTrucks();
		LoadCargos();
		PrintConsole();
		Sleep(1500);
		++CurrentTime;
		incrementWHs();
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
	pUI->PrintEmptytrucks(this);
	pUI->PrintLine();
	pUI->PrintMovingCargos(this);
	pUI->PrintLine();
	pUI->PrintIn_CheckupTrucks(this);
	pUI->PrintLine();
	pUI->PrintDeliveredCargo(this);
	pUI->PrintLine();
}

void Company::InteractiveSimulation() {
	int cnt = 10;
	while (cnt++) {
		ExecuteEvents();
		LoadCargos();
		incrementWHs();
		checkforAutop();
		PrintConsole();
		++CurrentTime;
		pUI->getKey();
		
	}
}

void Company::checkforAutop() {
	Cargo* cptr;
	Queue<Cargo*>q;
	while (WaitingNormalCargos.DeleteFirst(cptr))
	{
		
		if (cptr->GetWaitingHours() > AutoP) {
			if (cptr) {
				VIPCargo* temp = new VIPCargo();
				temp->SetCost(cptr->getCost());
				temp->SetDdes(cptr->getDis());
				temp->SetID(cptr->GetID());
				temp->SetLT(cptr->getLT());
				temp->setPT(cptr->getPT().getDAY(), cptr->getPT().gethour());
				AddCargotoVIPWaiting(temp);
			}
			this->set_NumberOfAutoPromotedCargos(this->get_NumberOfAutoPromotedCargos() + 1);
		}
		else q.enqueue(cptr);
		
	}
	while (q.dequeue(cptr))
		WaitingNormalCargos.InsertEnd(cptr);
}

void Company::OutputFile() {			//ismail
	//ofstream Lfile;
	//Lfile.open("Output.txt", ios::binary);
	//Lfile << "CDT\t\tID\t\tWT\t\tTID\n";
	//Cargo* cargo;
	//bool bo;
	//for (int i = 0; i < DeliveredNormalCargo.GetCount(); i++)
	//{

	//	bo = DeliveredNormalCargo.dequeue(cargo);
	//	Lfile << /* CARGO DELIVERED DAY*/<<':'<</* CARGO DELIVERED HOUR*/<<"\t\t" << cargo->GetID() << "\t\t" << cargo->getPT().getDAY() << ':' << cargo->getPT().gethour() << cargo->GetWaitingHours() << "\t\t" << cargo->get_TrkId() << endl;
	//	bo = DeliveredNormalCargo.enqueue(cargo);
	//}
	//for (int i = 0; i < DeliveredSpCargo.GetCount(); i++)
	//{

	//	bo = DeliveredSpCargo.dequeue(cargo);
	//	Lfile <<  /* CARGO DELIVERED DAY*/<<':'<</* CARGO DELIVERED HOUR*/<<"\t\t" << cargo->GetID() << "\t\t" << cargo->getPT().getDAY() << ':' << cargo->getPT().gethour() << cargo->GetWaitingHours() << "\t\t" << cargo->get_TrkId() << endl;
	//	bo = DeliveredSpCargo.enqueue(cargo);
	//}
	//for (int i = 0; i < DeliveredVIPCargo.GetCount(); i++)
	//{

	//	bo = DeliveredVIPCargo.dequeue(cargo);
	//	Lfile << /* CARGO DELIVERED DAY*/<<':'<</* CARGO DELIVERED HOUR*/<<"\t\t" << cargo->GetID() << "\t\t" << cargo->getPT().getDAY() << ':' << cargo->getPT().gethour() << cargo->GetWaitingHours() << "\t\t" << cargo->get_TrkId() << endl;
	//	bo = DeliveredVIPCargo.enqueue(cargo);
	//}


	//Lfile << ".....................................................\n";
	//Lfile << ".....................................................\n";
	//Lfile << "Cargos: " << GetnumOfDeliv();
	//Lfile << '[' << "N: " << DeliveredNormalCargo.GetCount() << ", " << "S: " << DeliveredSpCargo.GetCount() << ", " << "V: " << DeliveredVIPCargo.GetCount() << "]\n";
	//Lfile << "Cargo Avg Wait = " << AverageWaitingTime_DeliveredNormalCargos().getDAY() + AverageWaitingTime_DeliveredSpecialCargos().getDAY() + AverageWaitingTime_DeliveredVIPCargos().getDAY();
	//Lfile << ':' << AverageWaitingTime_DeliveredNormalCargos().gethour() + AverageWaitingTime_DeliveredSpecialCargos().gethour() + AverageWaitingTime_DeliveredVIPCargos().gethour() << endl;
	//Lfile << "Auto-promoted Caros:" << int((float(this->get_NumberOfAutoPromotedCargos()) / DeliveredNormalCargo.GetCount()) * 100) << "%\n";
	//Lfile << "Trucks: " << get_numOf_N_Truck() + get_numOf_S_Truck() + get_numOf_VIP_Truck();
	//Lfile << '[' << "N: " << get_numOf_N_Truck() << ", " << "S: " << get_numOf_S_Truck() << ", " << "V: " << get_numOf_VIP_Truck() << "]\n";
	//Lfile << "Avg Active time = " << NormalTrucks_ActiveTime().gethour() + NormalTrucks_ActiveTime().getDAY() * 24 + SpecialTrucks_ActiveTime().gethour() + SpecialTrucks_ActiveTime().getDAY() * 24 + VIPTrucks_ActiveTime().gethour() + VIPTrucks_ActiveTime().getDAY() * 24 << "%\n";
	//Lfile << "Avg utilization = " << NormalTrucks_Utilization() + SpecialTrucks_Utilization() + VIPTrucks_Utilization() << "%\n";

	//Lfile.close();
}
Time Company::AverageWaitingTime_DeliveredNormalCargos()
{
	Cargo* cargo;
	Time time;
	bool bo;
	for (int i = 0; i < DeliveredNormalCargo.GetCount(); i++)
	{
		bo = DeliveredNormalCargo.dequeue(cargo);
		time = time + cargo->GetWaitingHours();
		bo = DeliveredNormalCargo.enqueue(cargo);
	}

	return time;
}
Time Company::AverageWaitingTime_DeliveredSpecialCargos()
{
	Cargo* cargo;
	Time time;
	bool bo;
	for (int i = 0; i < DeliveredSpCargo.GetCount(); i++)
	{
		bo = DeliveredSpCargo.dequeue(cargo);
		time = time + cargo->GetWaitingHours();
		bo = DeliveredSpCargo.enqueue(cargo);
	}
	return time;
}
Time Company::AverageWaitingTime_DeliveredVIPCargos()
{
	Cargo* cargo;
	Time time;
	bool bo;
	for (int i = 0; i < DeliveredVIPCargo.GetCount(); i++)
	{
		bo = DeliveredVIPCargo.dequeue(cargo);
		time = time + cargo->GetWaitingHours();
		bo = DeliveredVIPCargo.enqueue(cargo);
	}
	return time;
}
void Company::set_NumberOfAutoPromotedCargos(int i)
{
	this->NumberOfAutoPromotedCargos = i;
}
int Company::get_NumberOfAutoPromotedCargos()
{
	return this->NumberOfAutoPromotedCargos;
}

int Company::get_numOf_N_Truck()
{
	return this->N;
}

int Company::get_numOf_S_Truck()
{
	return this->S;
}

int Company::get_numOf_VIP_Truck()
{
	return this->V;
}

Time Company::NormalTrucks_ActiveTime()
{
	Time time;
	Truck* truck;
	bool bo;
	for (int i = 0; i < NormalTrucks.GetCount(); i++)
	{
		bo = NormalTrucks.dequeue(truck);
		time.sethour(time.gethour() + truck->get_ActiveTime().gethour() + 24 * truck->get_ActiveTime().getDAY());
		bo = NormalTrucks.enqueue(truck);
	}
	return time;
}

Time Company::SpecialTrucks_ActiveTime()
{
	Time time;
	Truck* truck;
	bool bo;
	for (int i = 0; i < SpecialTrucks.GetCount(); i++)
	{
		bo = SpecialTrucks.dequeue(truck);
		time.sethour(time.gethour() + truck->get_ActiveTime().gethour() + 24 * truck->get_ActiveTime().getDAY());
		bo = SpecialTrucks.enqueue(truck);
	}
	return time;
}

Time Company::VIPTrucks_ActiveTime()
{
	Time time;
	Truck* truck;
	bool bo;
	for (int i = 0; i < VIPTrucks.GetCount(); i++)
	{
		bo = VIPTrucks.dequeue(truck);
		time.sethour(time.gethour() + truck->get_ActiveTime().gethour() + 24 * truck->get_ActiveTime().getDAY());
		bo = VIPTrucks.enqueue(truck);
	}
	return time;
}

int Company::NormalTrucks_Utilization()
{
	Truck* truck;
	bool bo;
	int count = 0;
	for (int i = 0; i < NormalTrucks.GetCount(); i++)
	{
		bo = NormalTrucks.dequeue(truck);
		count = count + truck->Truck_utilization();
		bo = NormalTrucks.enqueue(truck);
	}
	return count;
}

int Company::SpecialTrucks_Utilization()
{
	Truck* truck;
	bool bo;
	int count = 0;
	for (int i = 0; i < SpecialTrucks.GetCount(); i++)
	{
		bo = SpecialTrucks.dequeue(truck);
		count = count + truck->Truck_utilization();
		bo = SpecialTrucks.enqueue(truck);
	}
	return count;
}

int Company::VIPTrucks_Utilization()
{
	Truck* truck;
	bool bo;
	int count = 0;
	for (int i = 0; i < VIPTrucks.GetCount(); i++)
	{
		bo = VIPTrucks.dequeue(truck);
		count = count + truck->Truck_utilization();
		bo = VIPTrucks.enqueue(truck);
	}
	return count;
}
void Company::incrementWHs() {
	WaitingNormalCargos.incrementWH();//List
	//===
	Queue<Cargo*>tq;
	Cargo* ct;
	while (WaitingSpecialCargos.dequeue(ct)) {
		ct->IncrementWaitingHours();
		tq.enqueue(ct);
	}
	while (tq.dequeue(ct))
		WaitingSpecialCargos.enqueue(ct);
	//===
	while (WaitingVIPCargos.dequeue(ct)) {
		ct->IncrementWaitingHours();
		tq.enqueue(ct);
	}
	while (tq.dequeue(ct))
		WaitingVIPCargos.enqueue(ct, ct->Getpriority());
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
	//Event* E;
	//int cnt = 0;
	//EventsPQ.peak(E);
	//while (EventsPQ.GetCount()>0) {
	//	cnt++;
	//	if (dynamic_cast<PromotionEvent*> (E)) cout << "PRE";
	//	if (dynamic_cast<CancellationEvent*> (E)) cout << "CE";
	//	if (dynamic_cast<PreparationEvent*> (E)) cout << "PE";
	//	cout << cnt << endl;
	//	EventsPQ.dequeue(E);
	//	cout << "ID: " << E->getID() << endl;
	//	//EventsPQ.peak(E);
	//}
	cout << N << " " << S << " " << V << endl;;
	cout << NormalEmptyTrucks.GetCount() << " " << SpecialEmptyTrucks.GetCount() << " " << VIPEmptyTrucks.GetCount() << endl;
}

void Company::CancellationID(int id)
{
	WaitingNormalCargos.Remove(id);
}

NormalCargo* Company::GetNormalCargo(int id) {
	if (WaitingNormalCargos.PointerToNormalCRGO(id))
		return dynamic_cast<NormalCargo*>(WaitingNormalCargos.PointerToNormalCRGO(id)->getitem());
	else return nullptr;
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
int Company::GetnumMoving() {
	return  MovingTrucks.GetCount();
}
void Company::PrintMoving(UIClass* pUI) {
	Queue<Truck*>q;
	Truck* tptr;
	while (MovingTrucks.dequeue(tptr)) {
		cout << tptr->getTimeforDelivery().getDAY() << ":" << tptr->getTimeforDelivery().gethour()<<" ID:";
		q.enqueue(tptr);
		pUI->Print(tptr);
		if (dynamic_cast<VIPTruck*>(tptr))
		{
			pUI->openbraceforVIP();
			tptr->Print(pUI);
			pUI->closebraceforVIP();
		}
		else if (dynamic_cast<NormalTruck*>(tptr))
		{
			pUI->openbraceforNormal();
			tptr->Print(pUI);
			pUI->closebraceforNormal();
		}
		else if (dynamic_cast<SpecialTruck*>(tptr))
		{
			pUI->openbraceforSP();
			tptr->Print(pUI);
			pUI->closebraceforSP();
		}
	}
	//while(q.dequeue(tptr))
		//MovingTrucks.enqueue(tptr,)   waiting for priority
}
void Company::PrintNInCheckupTRKs(UIClass* pUI) {
	if (NInCheckupTrucks.GetCount() > 0) {
		pUI->openbraceforNormal();
		NInCheckupTrucks.PrintQ(pUI);
		pUI->closebraceforNormal();
	}
}
void Company::PrintSInCheckupTRKs(UIClass* pUI) {
	if (SInCheckupTrucks.GetCount() > 0) {
		pUI->openbraceforSP();
		SInCheckupTrucks.PrintQ(pUI);
		pUI->closebraceforSP();
	}
}
void Company::PrintVInCheckupTRKs(UIClass* pUI) {
	if (VInCheckupTrucks.GetCount() > 0) {
		pUI->openbraceforVIP();
		VInCheckupTrucks.PrintQ(pUI);
		pUI->closebraceforVIP();
	}
}
int Company::GetCountTRUCKSincheckup() {
	return NInCheckupTrucks.GetCount() + SInCheckupTrucks.GetCount() + VInCheckupTrucks.GetCount();
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
void Company::printEmptyTrucks(UIClass* pUI) {
	if (VIPEmptyTrucks.GetCount() > 0) {
		pUI->openbraceforVIP();
		VIPEmptyTrucks.PrintQ(pUI);
		pUI->closebraceforVIP();
	}
	if (NormalEmptyTrucks.GetCount() > 0) {
		pUI->openbraceforNormal();
		NormalEmptyTrucks.PrintQ(pUI);
		pUI->closebraceforNormal();
	}
	if (SpecialEmptyTrucks.GetCount() > 0) {
		pUI->openbraceforSP();
		SpecialEmptyTrucks.PrintQ(pUI);
		pUI->closebraceforSP();
	}
}
int Company::GetNumOfEmptyTrcs() {
	return VIPEmptyTrucks.GetCount() + NormalEmptyTrucks.GetCount() + SpecialEmptyTrucks.GetCount();
}
void Company::CheckforCargosExceededMaxW() {
	// Normal Check 
	Cargo* C = nullptr;
	if (WaitingNormalCargos.GetCount() > 0) {
		C = WaitingNormalCargos.getHead()->getitem();
		while (C&&C->GetWaitingHours() >= MaxW) {
			WaitingNormalCargos.DeleteFirst(C);
			NCargosExceededMaxW.enqueue(C);
			C = nullptr;
			if(WaitingNormalCargos.getHead())
			C = WaitingNormalCargos.getHead()->getitem();
		}
	}
	//Special Check
	if (WaitingSpecialCargos.GetCount() > 0) {
		WaitingSpecialCargos.peak(C);
		while (C&&C->GetWaitingHours() >= MaxW) {
			WaitingSpecialCargos.dequeue(C);
			SCargosExceededMaxW.enqueue(C);
			C = nullptr;
			WaitingSpecialCargos.peak(C);
		}
	}
	//VIP check 
	if (WaitingVIPCargos.GetCount() > 0) {
		WaitingVIPCargos.peak(C);
		while (WaitingVIPCargos.GetCount()>0&&C->GetWaitingHours() >= MaxW) {
			WaitingVIPCargos.dequeue(C);
			VCargosExceededMaxW.enqueue(C);
			WaitingVIPCargos.peak(C);
		}
	}

}
bool Company::AssignVIP() {
	Cargo* VC;
	if (VIPEmptyTrucks.GetCount() > 0 && VTruckCapacity <= WaitingVIPCargos.GetCount()) {
		AssignVIPTruck(0);
		return true;
	}
	else if (NormalEmptyTrucks.GetCount() > 0 && NTruckCapacity <= WaitingVIPCargos.GetCount()) {
		AssignNormalTruck(0);
		return true;
		
	}
	else if (SpecialEmptyTrucks.GetCount() > 0 && STruckCapacity <= WaitingVIPCargos.GetCount()) {
		AssignSpecialTruck(0);
		return true;
	}
	else {
		return false;
	}
}
bool Company::AssignSpecial() {
	Cargo* SC;
	if (SpecialEmptyTrucks.GetCount() > 0 && STruckCapacity <= WaitingVIPCargos.GetCount()) {
		AssignSpecialTruck(1);
		return true;
	}
	return false;
}
bool Company::AssignNormal() {
	if (NormalEmptyTrucks.GetCount() > 0 && NTruckCapacity <= WaitingNormalCargos.GetCount()) {
		AssignNormalTruck(1);
		return true;
	}
	else if (VIPEmptyTrucks.GetCount() > 0 &&VTruckCapacity <= WaitingNormalCargos.GetCount()) {
		AssignVIPTruck(1);
		return true;
	}
	return false;
}
void Company::AssignVIPTruck(int T) {
		Cargo* C = nullptr;
		Truck* VT;
		bool CangoNow = false;
		if (VIPEmptyTrucks.GetCount() == 0) return;
		VIPEmptyTrucks.dequeue(VT);
		while (!VT->isFull()) {
			if (T == 0&& WaitingVIPCargos.GetCount()>0)WaitingVIPCargos.dequeue(C);
			else if(T==1 && WaitingNormalCargos.GetCount() > 0) WaitingNormalCargos.DeleteFirst(C);
			else if (T == 2 && VCargosExceededMaxW.GetCount() > 0) {
				VCargosExceededMaxW.dequeue(C);
				if (VCargosExceededMaxW.GetCount() == 0)CangoNow = true;
			}
			else if (T == 3 && SCargosExceededMaxW.GetCount() > 0) {
				SCargosExceededMaxW.dequeue(C);
				if (SCargosExceededMaxW.GetCount() == 0) CangoNow = true;
			}
			if (!C) break;
			VT->AddCargo(C);
			if (CangoNow) break;
		}
		VT->incrementJC();
		VT->updateDI();
		VT->setTimeforDelivery(this->CurrentTime );
		VT->setTimeforReturn(this->CurrentTime);
		VT->setTimeforLoading(this->CurrentTime);
		LoadingTrucks.enqueue(VT);
}
void Company::AssignNormalTruck(int T) {
		Cargo* C = nullptr;
		Truck* NT = nullptr;
		if (NormalEmptyTrucks.GetCount() == 0) return;
		NormalEmptyTrucks.dequeue(NT);
		bool CangoNow = false;
		while (NT&&!NT->isFull()) {
			if (T == 0 &&WaitingVIPCargos.GetCount()>0)WaitingVIPCargos.dequeue(C);
			else if (T == 1 && WaitingNormalCargos.GetCount() > 0) {
				WaitingNormalCargos.DeleteFirst(C);
			}
			else if (T == 2 && VCargosExceededMaxW.GetCount() > 0) {
				VCargosExceededMaxW.dequeue(C);
				if(VCargosExceededMaxW.GetCount()==0)CangoNow = true;
			}
			else if (T == 3 && NCargosExceededMaxW.GetCount() > 0) {
				NCargosExceededMaxW.dequeue(C);
				if (NCargosExceededMaxW.GetCount() == 0) CangoNow = true;
			}
			if (!C) break;
			NT->AddCargo(C);
			if (CangoNow) break;
		}
		NT->incrementJC();
		NT->updateDI();
		NT->setTimeforDelivery(this->CurrentTime);
		NT->setTimeforReturn(this->CurrentTime);
		NT->setTimeforLoading(this->CurrentTime);
		LoadingTrucks.enqueue(NT);
}
void Company::AssignSpecialTruck(int T) {
	Cargo* C = nullptr;
	Truck* ST;
	bool CangoNow = false;
	if (SpecialEmptyTrucks.GetCount() == 0) return;
	SpecialEmptyTrucks.dequeue(ST);
	while (!ST->isFull()) {
		if (T == 0&&WaitingVIPCargos.GetCount()>0) WaitingVIPCargos.dequeue(C);
		else if (T == 1&&WaitingSpecialCargos.GetCount()>0)WaitingSpecialCargos.dequeue(C);
		else if (T == 2 && VCargosExceededMaxW.GetCount() > 0) {
			VCargosExceededMaxW.dequeue(C);
			if (VCargosExceededMaxW.GetCount() == 0)CangoNow = true;
		}
		else if (T == 3 && SCargosExceededMaxW.GetCount() > 0) {
			SCargosExceededMaxW.dequeue(C);
			if (SCargosExceededMaxW.GetCount() == 0) CangoNow = true;
		}
		if (!C) break;
		ST->AddCargo(C);
		ST->updateDI();
		ST->setTimeforDelivery(this->CurrentTime);
		ST->setTimeforReturn(this->CurrentTime);
		ST->setTimeforLoading(this->CurrentTime);
		if (CangoNow) break;
	}
	ST->incrementJC();
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
void Company::CreateTrucks() {
		int cnt = N;
		while (cnt--) {
			NormalTruck* N = new NormalTruck(++TruckCount,NTruckCapacity,NTruckSpeed);
			NormalEmptyTrucks.enqueue(N);
		}
		cnt = S;
		while (cnt--) {
			SpecialTruck* N = new SpecialTruck(++TruckCount, NTruckCapacity, NTruckSpeed);
			SpecialEmptyTrucks.enqueue(N);
		}
		cnt = V;
		while (cnt--) {
			VIPTruck* N = new VIPTruck(++TruckCount, NTruckCapacity, NTruckSpeed);
			VIPEmptyTrucks.enqueue(N);
		}
}
void Company::CheckforCheckupTrucks() {
	Truck* T; 
	Queue<Truck* >temp;
	// Check for normal
	while (NormalEmptyTrucks.GetCount() > 0 && NormalEmptyTrucks.dequeue(T)) {
		if (T->getJC() >= JourneyCount)NInCheckupTrucks.enqueue(T);
		else temp.enqueue(T);
		}
	while (temp.GetCount() > 0 && temp.dequeue(T))NormalEmptyTrucks.enqueue(T);

	// Check for VIP

	while (NormalEmptyTrucks.GetCount() > 0 && NormalEmptyTrucks.dequeue(T)) {
		if (T->getJC() >= JourneyCount)NInCheckupTrucks.enqueue(T);
		else temp.enqueue(T);
	}
	while (temp.GetCount() > 0 && temp.dequeue(T))NormalEmptyTrucks.enqueue(T);
	
}
void Company::CheckforTrucks() {
	Truck* T;
	Queue<Truck* > temp;
	while (LoadingTrucks.GetCount() > 0) {
		LoadingTrucks.dequeue(T);
		if (T->getTimeforLoading() == CurrentTime) {
			MovingTrucks.enqueue(T, 0);
		}
		else {
			temp.enqueue(T);
		}
		T = nullptr;
	}
	while (temp.GetCount() > 0) {
		temp.dequeue(T);
		LoadingTrucks.enqueue(T);
	}
	while (MovingTrucks.GetCount() > 0) {
		MovingTrucks.dequeue(T);
		if (T->getTimeforDelivery() == CurrentTime) {
			Deliver(T);
			//temp.enqueue(T);
		}
		else if (T->getTimeforReturn() == CurrentTime) {
			if (dynamic_cast<NormalTruck*> (T)) NormalEmptyTrucks.enqueue(T);
			else if (dynamic_cast<SpecialTruck*> (T)) SpecialEmptyTrucks.enqueue(T);
			else VIPEmptyTrucks.enqueue(T);
		}
		else {
			temp.enqueue(T);
		}
	}
	while (temp.GetCount() > 0) {
		temp.dequeue(T);
		MovingTrucks.enqueue(T,0);
	}
}
void Company::Deliver(Truck* T) {
	Cargo* C = nullptr;
	while (T->RemoveCargo(C)&&C) {
		if (dynamic_cast<VIPCargo*>(C)) DeliveredVIPCargo.enqueue(C);
		else if (dynamic_cast<NormalCargo*>(C)) DeliveredNormalCargo.enqueue(C);
		else DeliveredSpCargo.enqueue(C);
		C = nullptr;
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