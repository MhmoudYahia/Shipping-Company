#include "UIClass.h"
#include "Queue.h"
#include "NormalTruck.h"
#include "VIPTruck.h"
#include "SpecialTruck.h"
#include"Cargo.h"
#include"List.h"
#include"PriorityQueue.h"
#include"Company.h"
template<class T>
class Queue;
class Truck;
template<class T>
class PriorityQueue;
UIClass::UIClass()
{

}

UIClass::~UIClass()
{
}

void UIClass::getKey()
{
	string s;
	cout <<"\nenter any key to continue\n";
	cin >> s;
}

Mode UIClass::SelectMode()
{
	int i;
	//Mode M;//as a default{}{}
	//cout << "if you want interactive or step-by-step or silent mode write 0 or 1 or 2 respectively\n";
	cout << "choose what you want\n0=====>interactive mode\n1=====>stepBystep mode\n2=====>silent mode\n";
	cin >> i;
		if (i == 0)
			return interactive;
		else if (i == 1)
			return step_by_step;
		else if (i == 2)
			return silent;
		else cout << "NOT VALID\n";
		
}

void UIClass::PrintLine()
{
	cout << "\n----------------------------------------------------------------------------------------------------------------\n";
}
template<class t>
void UIClass::Print(t c)
{
	cout << c;
}
template<>
void UIClass::Print(Cargo*c)
{
	int h = c->getDel_T().gethour(); int d = c->getDel_T().getDAY();
	cout << c->GetID()<<" WHs: "<<c->GetWaitingHours()<<"  DT "<<d<<":"<<h;
}
template<>
void UIClass::Print(Truck* t)
{
	cout << t->GetID();
}
template<>
void UIClass::Print(NormalTruck* t) {
	cout << t->GetID();
}
template<>
void UIClass::Print(SpecialTruck* t) {
	cout << t->GetID();
}
template<>
void UIClass::Print(VIPTruck* t) {
	cout << t->GetID();
}
void UIClass::PrintSilentMode(Company* Cptr)
{
	cout << "SilentMode\n" << "Simulation Starts...\n" << "Simulation ends, Output file created\n";
	//Cptr->OutputFile();
}

void UIClass::PrintError(string msg) {
	cout << "Error: " << msg << endl;
}
void UIClass::PrintCurrentTime(Time T)
{
	cout << "\nCurrent Time (Day:Hour):" << T.getDAY() << ":" << T.gethour() << endl;
}
void UIClass::openbraceforNormal() {
	cout << '[';
}
void UIClass::closebraceforNormal() {
	cout << "] ";
}
void UIClass::openbraceforVIP() {
	cout << '{';
}
void UIClass::closebraceforVIP() {
	cout << "} ";
}
void UIClass::openbraceforSP() {
	cout << '(';
}
void UIClass::closebraceforSP() {
	cout << ") ";
}
void UIClass::PrintWaitingCargos(Company* Cptr) {
	cout << Cptr->Getcountall_waiting() << " Waiting Cargo: ";
	Cptr->printWaitingNormal(this);
	Cptr->printWaitingSP(this);
	Cptr->printWaitingVIP(this);
	
}


void UIClass::PrintMovingCargos(Company* Cptr)
{
	cout <<Cptr->GetnumMoving()<< " Moving Cargos: ";
	Cptr->PrintMoving(this);
}
void UIClass::Printcomma() {
	cout << ',';
}
void UIClass::PrintDeliveredCargo(Company*Cptr) // 
{
	cout << Cptr->GetnumOfDeliv() << " Delivered Cargos: ";

	Cptr->printDelivered(this);
	
}
void UIClass::PrintIn_CheckupTrucks(Company*C)
{
	cout << C->GetCountTRUCKSincheckup() << " Incheckup Trucks: ";
	C->PrintNInCheckupTRKs(this);
	C->PrintSInCheckupTRKs(this);
	C->PrintVInCheckupTRKs(this);
}
void UIClass::PrintMaintenenceTrucks(Company* C)
{
	cout << C->GetCountTRKsMaintence() << " Maintenence Trucks: ";
	C->PrintNMaintenenceTRKs(this);
	C->PrintSMaintenenceTRKs(this);
	C->PrintVMaintenenceTRKs(this);
}
void UIClass::PrintEmptytrucks(Company* pC)
{
	cout << pC->GetNumOfEmptyTrcs() << " Empty Trucks: ";
	pC->printEmptyTrucks(this);

}
void UIClass::PrintLoadingTrucks(Company* c) {
	cout << c->GetNumOfLaoding() << " Loading Trucks: ";
	c->PrintLoading(this);
}
