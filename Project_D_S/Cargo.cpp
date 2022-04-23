#include "Cargo.h"
#include "Truck.h"

Cargo::Cargo()
{
	this->cost = 0;
	this->ID = -1;
	this->TrkId = -1;
	this->delvr_Dis = 0;
	this->Load_T = 0;
	this->Per_T.first = 0;
	this->Per_T.second = 0;
	this->WaitingH = 0;
}
Cargo::Cargo( int cost, int LT, int DIS,int ID, int H, int D) {
	setPT(D, H);
	SetCost(cost);
	SetLT(LT);
	SetDdes(DIS);
	SetID(ID);
}


int Cargo::GetTid()
{
	return TrkId;
}

void Cargo::SetTid(int i)
{
	this->TrkId = i;
}

void Cargo::ChangeState(State c)
{
	Cargostate = c;
}

State Cargo::GetState()
{
	return Cargostate;
}

void Cargo::setPT(int d, int h)
{
	this->Per_T.Day =(d>0)? d:0;
	this->Per_T.hour = (h >= 0 && h < 24) ? h : 0;
}

void Cargo::SetLT(double t)
{
	this->Load_T = (t > 0) ? t : 0;
}

void Cargo::SetDdes(double d)
{
	this->delvr_Dis = (d > 0) ? d : 0;
}

void Cargo::SetCost(double c)
{
	this->cost = (c > 0) ? c : 0;
}

void Cargo::SetID(int d)
{
	ID = (d > 0) ? d : 0;
}

int Cargo::GetID()
{
	return ID;
}

int Cargo::Getpriority()
{
	return 0;
}

double Cargo::getDdes()
{
	return delvr_Dis;
}

double Cargo::getCost()
{
	return cost;
}

double Cargo::getLT()
{
	return Load_T;
}

pair<int, int> Cargo::getPT()
{
	return Per_T;
}
void Cargo::IncrementWaitingHours() {
	WaitingH++;
}
int Cargo::GetWaitingHours() {
	return WaitingH;
}
Cargo::~Cargo()
{
}
