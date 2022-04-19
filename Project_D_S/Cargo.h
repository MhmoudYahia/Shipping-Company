#pragma once
#include<iostream>
using namespace std;
#include<utility>
enum State { waiting, moving, delivered };
class Cargo
{
protected:
	State Cargostate;
	pair<int, int>Per_T;
	double Load_T;
	double delvr_Dis;
	double cost;
	int WaitingH;
	int ID;
public:
	Cargo() ;  // will come back
	void ChangeState(State c);
	State GetState();
	virtual void setPT(int d, int h);
	virtual void SetLT(double t);
	virtual void SetDdes(double d);
	virtual void SetCost(double c);
	void IncrementWaitingHours();
	int GetWaitingHours();
    void SetID(int d);
	int GetID();
	double getDdes();		//ismail
	double getCost();		//ismail
	double getLT();		//ismail
	pair<int, int> getPT();		//ismail
	~Cargo();
};

