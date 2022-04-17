#pragma once
#include "Queue.h"
#include "PriorityQueue.h"
#include "Cargo.h"
#include "Truck.h"
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


};

