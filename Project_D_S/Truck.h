#pragma once

#include "Queue.h"
#include "Cargo.h"
enum State  {Loading, Empty, InCheckUp};

class Truck
{
	int ID; // 1 for VIP , 2 for Normal , 3 for Special 
	int TC; //TruckCapacity
	State TruckState;
	int CargoCount; 
	int MaintenanceTime; // In hours
	double Speed; //In Km/Hour 
	Queue<Cargo* > TruckCargos;
	double DI; //Delivery Interval =(Distance of furthest cargo)/ speed + Sum of unload times of all its cargos + time to come back
	
public:
	void ChangeState(State S) {
		TruckState = S;
		CargoCount = 0;
	}
	Truck(int T) {
		if (T > 0) TC = T;

	}
	bool AddCargo(Cargo* C) {
		if (CargoCount == TC) {
			cout << "The Truck is full\n";
			return false;
		}
		TruckCargos.enqueue(C);
		CargoCount++;
		return true;
	}
};

