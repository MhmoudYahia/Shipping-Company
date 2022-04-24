#pragma once
#include "Cargo.h"
class VIPCargo :
    public Cargo
{
    int Priority;
public:
    VIPCargo();
    VIPCargo(int ID, double P, int d, int h, double lt, double c,int dis);
    int Getpriority();
    void UpdatePriority();
    virtual void setPT(int d, int h);
    virtual void SetLT(double t);
    virtual void SetDis(double d);
    virtual void SetCost(double c);
    ~VIPCargo();
};

