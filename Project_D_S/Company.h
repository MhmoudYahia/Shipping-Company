#pragma once
#include "Queue.h"
#include "PriorityQueue.h"
#include "Cargo.h"
#include "Truck.h"
#include"PreparationEvent.h"
#include"PromotionEvent.h"
#include"CancellationEvent.h"
#include"Event.h"
#include"Time.h"
#include<fstream>
class Company
{

	// Cargos for Display
	PriorityQueue<Cargo*> WaitingCargos;
	Queue<Cargo*> MovingCargos;
	Queue<Cargo*> DeliveredCargos;

	// Trucks for display 
	Queue<Truck*> LoadingTrucks;
	Queue<Truck*> EmptyTrucks;
	Queue<Truck*> InCheckupTrucks;

	//Trucks
	Queue<Truck*>NormalTrucks;
	Queue<Truck*>SpecialTrucks;
	Queue<Truck*>VIPTrucks;

	//Cargos
	Queue<Cargo*>NormalCargos;
	Queue<Cargo*>SpecialCargos;
	Queue<Cargo*>VIPCargos;
	
	//Events
	Queue<PreparationEvent*> PreparationEvents;
	Queue<PromotionEvent*> PromotionEvents;
	Queue<CancellationEvent*> CancellationEvents;
	int MaxW;
	Time CurrentTime;

public:
	void LoadCargos();
	void IncrementHour();
	void setMaxW(int);
	void setcurtime(Time time);
	Time getcurtime();
	bool isClosed();
	bool AddtoVIPTruck(Cargo*);
	bool AddtoNormalTruck(Cargo*);
	bool AddtoSpecialTruck(Cargo*);
	void Update_UI_Interface();
	void Loading_File();
};

