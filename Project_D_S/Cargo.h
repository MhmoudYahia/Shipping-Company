#pragma once
#include<iostream>
using namespace std;
#include<utility>

class Cargo
{
protected:
	pair<int, int>Per_T;
	double Load_T;
	double delvr_Dis;
	double cost;
	int ID;
public:
	Cargo() ;  // will come back
	virtual void setPT(int d, int h);
	virtual void SetLT(double t);
	virtual void SetDdes(double d);
	virtual void SetCost(double c);
    void SetID(int d);
	int GetID();
	~Cargo();
};

