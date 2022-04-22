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

	void PrintID(Cargo*c);

	void PrintID(Truck*t);

	void PrintCurrentTime(pair<int, int>p);

	// interactiveExcute mode
	void printWaitingCargos(PriorityQueue<Cargo*>* qWc);

	void PrintMovingCargos(Queue<Cargo*>* qMc);

	void printDeliveredCargo(Queue<Cargo*>* qDc);

	void PrintIn_CheckupTrucks(Queue<Truck*>* qCt);

	void PrintEmptytrucks(Queue<Truck*>* qEt);
};

