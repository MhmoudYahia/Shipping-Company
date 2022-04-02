#pragma once
#include<iostream>
using namespace std;
#include<utility>

class Cargo
{
	pair<int, int>Per_T;
	double Load_T;
	double delvr_Dis;
	double cost;
	int ID;
public:
	Cargo() ;  // will come back
	void setPT(int d, int h);
	void SetLT(double t);
	void SetDdes(double d);
	void SetCost(double c);
	void SetID(int d);
	int GetID();
	~Cargo();
};

