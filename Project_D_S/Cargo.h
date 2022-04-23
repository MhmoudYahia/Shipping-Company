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
	int TrkId; // id of its truck(moving) <=> -1 if no truck(not moving) 
public:
	Cargo() ;  // will come back
	int GetTid();
	void SetTid(int i);
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
	virtual int Getpriority();  //return 0 except in vip
	double getDdes();		//ismail
	double getCost();		//ismail
	double getLT();		//ismail
	pair<int, int> getPT();		//ismail
	~Cargo();
};

