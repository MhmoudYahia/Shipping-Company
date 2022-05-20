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
	
	double pri_s_c;
	Time ActiveTime;
	int ID; 
	int State; //  0 for rest , 1 for loading , 2 for moving , 3 for checkup 
	Time TimeforDelivery;
	Time TimeforReturn;
	Time TimeforLoading;
	int TC; //TruckCapacity
	//State TruckState;
	int CargoCount;
	int MaintenanceTime; // In hours
	double Speed; //In Km/Hour 
	int JourneyCount;
	int HoursforGoingwithoutReturning;
	int DisofFurthestCargo;
	int LoadTimeofAllcargos;
	int Priority;
	Queue <Cargo* > * TruckCargos;
	int DI; //Delivery Interval =(Distance of furthest cargo)/ speed + Sum of unload times of all its cargos + time to come back
	Time putInMaintenanceTime;		//shaheen
	bool Night;
public:
	void UPdatePriority_s_c();
	double getprio_s_c();
	int GetID();
	//void ChangeState(State S);
	Truck(int ID , int TC , int TS , bool );
	bool AddCargo(Cargo* C);
	int GetCountOFCargosInTRK();
	void updateDI();
	int getDI();
	void incrementJC();
	void resetJC();
	int getJC();
	bool RemoveCargo(Cargo*& C);
	virtual void Print(UIClass*p);
	int GetnumofCRGS();
	void setSpeed(double);
	bool isFull();
	void set_ActiveTime();		//ismail
	Time get_ActiveTime();		//ismail
	int	Truck_utilization(int);
	int getPriority();
	Cargo* GetFurthestCargo();
	void updatePriority();
	int getHoursleftforDelivery();
	int getTimeleftforReturn();
	void decrementHoursleftforDelivery();
	void decrementTimeleftforReturn();
	void setTimeforReturn(Time );
	void setTimeforDelivery(Time);
	void setTimeforLoading(Time);
	Time getTimeforDelivery();
	Time getTimeforReturn();
	Time getTimeforLoading();
	void ResetDeliveryTime();
	Queue <Cargo* > getDelivered(Time);
	void updateCargosDT();
	void set_putInMaintenanceTime(Time t);		//shaheen
	Time get_putInMaintenanceTime();		//shaheen
	int get_MaintenanceTime();		//shaheen
	int getTC();
	void ResetCargoCount();
	bool CanWorkAtNight();
};