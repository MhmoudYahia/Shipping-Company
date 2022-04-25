#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"PriorityQueue.h"
#include"List.h"
#include"Cargo.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
#include"SpecialCargo.h"
#include"Time.h"
class Truck;
template<class T>
class Queue;
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
	void PrintQ(Queue < Cargo*>);
	void PrintQ(Queue < Truck*>);

	//time
	void PrintCurrentTime(Time T);

	//printing Cargos and Trucks Categories
	void printWaitingCargos(PriorityQueue<Cargo*> qWc);

	void PrintMovingCargos(Queue<Cargo*> qMc);

	void PrintDeliveredCargo(Queue<Cargo*> qDc);

	void PrintIn_CheckupTrucks(Queue<Truck*> qCt);

	void PrintEmptytrucks(Queue<Truck*> qEt);

	void PrintLoadingTrucks(Queue<Truck*>);

	//Silent mode interface
	void PrintSilentMode();
	void PrintError(string);


};

