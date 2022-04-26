#pragma once
#include "Cargo.h"
class SpecialCargo :
    public Cargo
{
public:
    SpecialCargo() {}
    SpecialCargo(int cost, int LT, int DIS, int ID, int H, int D);
    ~SpecialCargo(){}
};

