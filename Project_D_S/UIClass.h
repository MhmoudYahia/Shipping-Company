#pragma once
#include<iostream>
using namespace std;
#include<string>
class Cargo;
#include"NormalCargo.h"
#include"VIPCargo.h"
#include"SpecialCargo.h"
#include"Time.h"
class Truck;
template<class T>
class Queue;
template <class T>
class PriorityQueue;
class Company;
enum Mode { interactive, step_by_step, silent };
class UIClass
	
{
public:
	UIClass();
	~UIClass();
	void getKey();
	//general
	Mode SelectMode();
	void PrintLine();
	//for Queue
	template<class t>
	void Print(t c);
	template<>
	void Print(Cargo*c);
	template<>
	void Print(Truck * t);
	//time
	void PrintCurrentTime(Time T);
	void PrintWaitingCargos(Company* Cptr);
	//printing Cargos and Trucks Categories
//	void printWaitingCargos(PriorityQueue<Cargo*> qWc);
	void PrintMovingCargos(Company*Cptr);
	void Printcomma();
	void PrintDeliveredCargo(Company* Cptr);
	void PrintIn_CheckupTrucks(Company* C);
	void PrintEmptytrucks(Company* pC);
	void PrintLoadingTrucks(Company* c);
	void PrintSilentMode(Company* Cptr);	//ismail
	void PrintError(string);
	void openbraceforNormal();
	void closebraceforNormal();
	void openbraceforVIP();
	void closebraceforVIP();
	void openbraceforSP();
	void closebraceforSP();


};

