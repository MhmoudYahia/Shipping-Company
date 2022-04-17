#include "Cargo.h"

Cargo::Cargo()
{
	this->cost = 0;
	this->ID = 0;
	this->delvr_Dis = 0;
	this->Load_T = 0;
	this->Per_T.first = 0;
	this->Per_T.second = 0;
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
	this->Per_T.first =(d>0)? d:0;
	this->Per_T.second = (h >= 0 && h < 24) ? h : 0;
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

Cargo::~Cargo()
{
}
