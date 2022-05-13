#pragma once
#include<iostream>
using namespace std;
#include<utility>
//enum State { waiting, moving, delivered };
#include"Time.h"
class Cargo
{
protected:
	//State Cargostate;
	Time Per_T;
	int Load_T;
	int delvr_Dis;
	int cost;
	int WaitingH;
	int ID;
	int TrkId; // id of its truck(moving) <=> -1 if no truck(not moving) 
public:
	Cargo() ;  // will come back
	Cargo(int cost, int LT, int DIS, int ID, int H, int D);
	int GetTid();
	void set_TrkId(int i);
	int get_TrkId();
	void SetTid(int i);
	//void ChangeState(State c);
	//State GetState();
	virtual void setPT(int d, int h);
	virtual void SetLT(int t);
	virtual void SetDdes(double d);
	virtual void SetCost(int c);
	void IncrementWaitingHours();
	void resetWaitingHours();
	int GetWaitingHours();
    void SetID(int d);
	int GetID();
	virtual double Getpriority();  //return 0 except in vip
	int getDis();		//ismail
	double getCost();		//ismail
	double getLT();		//ismail
    Time getPT();		//ismail
	~Cargo();
};

