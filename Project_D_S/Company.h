#pragma once
#include"UIClass.h"
#include "Queue.h"
#include "VIPTruck.h"
#include "NormalTruck.h"
#include "SpecialTruck.h"
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
	int TruckCount; 
	// Cargos for Display
	//PriorityQueue<Cargo*> WaitingCargos;
	//Queue<Cargo*> DeliveredCargos;

	// Trucks loading
	Queue<Truck*> LoadingTrucks;

	//Incheckuptrucks
	Queue<Truck*> NInCheckupTrucks;
	Queue<Truck*> SInCheckupTrucks;
	Queue<Truck*> VInCheckupTrucks;

	//Queue<Truck*> EmptyTrucks;
	Queue<Truck*> VIPEmptyTrucks;
	Queue<Truck*> NormalEmptyTrucks;
	Queue<Truck*> SpecialEmptyTrucks;
	//moving  may be edited under assignment criteria	Queue<Cargo*> MovingCargos;

	//Trucks
	Queue<Truck*>NormalTrucks;
	Queue<Truck*>SpecialTrucks;
	Queue<Truck*>VIPTrucks;

	PriorityQueue<Truck* > MovingTrucks;
	//=================================
	//Cargos Waiting   
	List<Cargo*>WaitingNormalCargos;
	Queue<Cargo*>WaitingSpecialCargos;
	PriorityQueue<Cargo*>WaitingVIPCargos;
	
	Queue<Cargo* > NCargosExceededMaxW;
	Queue<Cargo* > SCargosExceededMaxW;
	Queue<Cargo* > VCargosExceededMaxW;


	//Cargos delivered /////////////////
	Queue<Cargo*>DeliveredNormalCargo;//will make them one q later
	Queue<Cargo*>DeliveredSpCargo;//
	Queue<Cargo*>DeliveredVIPCargo;//

	//Events
	PriorityQueue<Event*> EventsPQ;   //need editing
	
	
	Time CurrentTime;
	UIClass* pUI;
	
	//Utility functions
	void StepbyStepSimulation();
	void PrintConsole();
	void InteractiveSimulation();
	void checkforAutop();
	void incrementWHs();
public:
	Company();
	void LoadCargos();
	//void IncrementHour();
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
	int GetnumMoving();
	void PrintMoving(UIClass* pUI);
	void PrintNInCheckupTRKs(UIClass* pUI);
	void PrintSInCheckupTRKs(UIClass* pUI);
	void PrintVInCheckupTRKs(UIClass* pUI);
	int GetCountTRUCKSincheckup();
	int Getcountall_waiting();
	int GetnumOfDeliv();
	void printDeliveredVIP(UIClass* pUI);
	void printDeliveredNormal(UIClass* pUI);
	void printDeliveredSP(UIClass* pUI);
	void printEmptyTrucks(UIClass* pUI);
	int GetNumOfEmptyTrcs();
	void CheckforCargosExceededMaxW();
	bool AssignNormal();
	bool AssignSpecial();
	bool AssignVIP();
	void AssignExceeded();
	void AssignSpecialTruck(int T); // 0 for VIP Cargos 1 for special Cargos 2 for VExceededCargos 3 for SExceededCargos
	void AssignNormalTruck(int T); // 0 for VIP Cargos 1 for Normal Cargos 2 for VExceededCargos 3 for NExceededCargos 
	void AssignVIPTruck(int T); // 0 for VIP Cargos 1 for Normal Cargos 2 for VExceededCargos 3 for NExceededCargos
	void CreateTrucks(); 
	void CheckforCheckupTrucks();
	void CheckforTrucks(); // Check for moving , loading , checkup 
	void Deliver(Truck*);

								
	//void AddCargotoVIPWaiting(Cargo* C);
	//void CancellationIDint id);
   //	void PrintDelivered(UIClass* pUI);
	//void AddCargotoWaiting(Cargo*);
//	bool UpdatetoVIP(int ID);
};

