#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"PriorityQueue.h"
#include"Queue.h"
#include"Cargo.h"
#include"Truck.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
#include"SpecialCargo.h"
#include"VIPTruck.h"
#include"SpecialTruck.h"
#include"NormalTruck.h"

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
	void PrintID(Cargo*c);

	void PrintID(Truck*t);

	//time
	void PrintCurrentTime(pair<int, int>p);

	//printing Cargos and Trucks Categories
	void printWaitingCargos(PriorityQueue<Cargo*>* qWc);

	void PrintMovingCargos(Queue<Cargo*>* qMc);

	void printDeliveredCargo(Queue<Cargo*>* qDc);

	void PrintIn_CheckupTrucks(Queue<Truck*>* qCt);

	void PrintEmptytrucks(Queue<Truck*>* qEt);

	void PrintLoadingTrucks(Queue<Truck*>* qLt);

	//Silent mode interface
	void PrintSilentMode();


};

