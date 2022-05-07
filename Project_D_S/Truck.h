#pragma once
template<class T>
class Queue;
#include "Queue.h"
#include "Cargo.h"
class UIClass;

//enum State  {Loading, Empty, InCheckUp};

class Truck
{
protected:
	int ID; 
	int State;
	int TC; //TruckCapacity
	//State TruckState;
	int CargoCount;
	int MaintenanceTime; // In hours
	double Speed; //In Km/Hour 
	int JourneyCount;
	Queue <Cargo* > * TruckCargos;
	double DI; //Delivery Interval =(Distance of furthest cargo)/ speed + Sum of unload times of all its cargos + time to come back

public:
	int GetID();
	//void ChangeState(State S);
	Truck(int ID , int TC , int TS );
	bool AddCargo(Cargo* C);
	void incrementJC();
	void resetJC();
	int getJC();
	bool RemoveCargo(Cargo* C);
	virtual void Print(UIClass*p);
	void setTruckCapacity(int);
	void setSpeed(double);
	bool isFull();
};