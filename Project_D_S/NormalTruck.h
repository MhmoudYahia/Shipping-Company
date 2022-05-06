#pragma once
#include "Truck.h"
class NormalTruck :
    public Truck
{
public:
    NormalTruck(int ID, int TC, int TS);
    void Print(UIClass* p);
   
};

