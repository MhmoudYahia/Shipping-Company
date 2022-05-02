#pragma once
#include"UIClass.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "Cargo.h"
#include "Truck.h"
#include"PreparationEvent.h"
#include"PromotionEvent.h"
#include"CancellationEvent.h"
#include"Event.h"
#include"Time.h"
#include"List.h"
#include<fstream>
class Company
{
	// Input file variables 
	
	int N; // Count of normal trucks 
	int S;	//Count of special trucks
	int V;	//Count of VIP trucks 
	int NTruckSpeed;
	int VTruckSpeed;
	int STruckSpeed;
	int NTruckCapacity;
	int VTruckCapacity;
	int STruckCapacity;
	int NTruckCheckupDuration;
	int STruckCheckupDuration; 
	int VTruckChekcupDuration; 
	int MaxW;
	int AutoP; // time for automatic promotion 
	int EventCount;
	int JourneyCount;


	// Cargos for Display
	//PriorityQueue<Cargo*> WaitingCargos;
	//Queue<Cargo*> DeliveredCargos;

	// Trucks for display 
	Queue<Truck*> LoadingTrucks;
	Queue<Truck*> EmptyTrucks;
	Queue<Truck*> InCheckupTrucks;

	//moving  may be edited under assignment criteria
	Queue<Cargo*> MovingCargos;

	//Trucks
	Queue<Truck*>NormalTrucks;
	Queue<Truck*>SpecialTrucks;
	Queue<Truck*>VIPTrucks;

	//Cargos Waiting  //M 
	List<Cargo*>WaitingNormalCargo;
	Queue<Cargo*>WaitingSpecialCargos;
	PriorityQueue<Cargo*>WaitingVIPCargos;

	//Cargos delivered  //M
	Queue<Cargo*>DeliveredNormalCargo;
	Queue<Cargo*>DeliveredSpCargo;
	Queue<Cargo*>DeliveredVIPCargo;

	//Events
	PriorityQueue<Event*> EventsPQ;
	
	
	Time CurrentTime;
	UIClass* pUI;
	
	//Utility functions
	void StepbyStepSimulation();
	void PrintConsole();
	void InteractiveSimulation();
public:
	Company();
	void LoadCargos();
	void IncrementHour();
	void setMaxW(int);
	void setcurtime(Time time);
	Time getcurtime();
	bool isClosed();
	/*bool AddtoVIPTruck(Cargo*);
	bool AddtoNormalTruck(Cargo*);
	bool AddtoSpecialTruck(Cargo*);*/
//	void Update_UI_Interface(Time T);
	void Loading_File();
	void GeneralSimulate();
	void OutputFile();
	void ExecuteEvents();
	void AddCargotoVIPWaiting(VIPCargo* C);
	void AddCargotoNormalWaiting(Cargo* n);
	void AddCargotoSpWaiting(SpecialCargo* n);
	void PrintEvents();
	void CancellationID(int id);
	NormalCargo* GetNormalCargo(int id);
	void printWaitingVIP(UIClass *);
	void printWaitingNormal(UIClass* pUI);
	void printWaitingSP(UIClass* pUI);
	int Getcountall_waiting();
	int GetnumOfDeliv();
	void printDeliveredVIP(UIClass* pUI);
	void printDeliveredNormal(UIClass* pUI);
	void printDeliveredSP(UIClass* pUI);

	//void AddCargotoVIPWaiting(Cargo* C);
	//void CancellationIDint id);
   //	void PrintDelivered(UIClass* pUI);
	//void AddCargotoWaiting(Cargo*);
//	bool UpdatetoVIP(int ID);
};

