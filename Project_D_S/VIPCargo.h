#pragma once
#include "Cargo.h"
class VIPCargo :
    public Cargo
{
    double Priority;
public:
    VIPCargo();
    VIPCargo(int c, int lt, double dis, int ID, int h, int d);
    double Getpriority();
    void UpdatePriority();
    virtual void setPT(int d, int h);
    virtual void SetLT(int t);
    virtual void SetDis(double d);
    virtual void SetCost(double c);
    ~VIPCargo();
};

