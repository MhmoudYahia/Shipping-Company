#pragma once
#include "Cargo.h"
class VIPCargo :
    public Cargo
{
    double Priority;
public:
    VIPCargo();
    VIPCargo(int ID, int d, int h, int lt, double c,double dis);
    double Getpriority();
    void UpdatePriority();
    virtual void setPT(int d, int h);
    virtual void SetLT(int t);
    virtual void SetDis(double d);
    virtual void SetCost(double c);
    ~VIPCargo();
};

