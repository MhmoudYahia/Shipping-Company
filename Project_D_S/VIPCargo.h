#pragma once
#include "Cargo.h"
class VIPCargo :
    public Cargo
{
    int Priority;
public:
    VIPCargo();
    int Getpriority();
    void UpdatePriority();
    virtual void setPT(int d, int h);
    virtual void SetLT(double t);
    virtual void SetDdes(double d);
    virtual void SetCost(double c);
    ~VIPCargo();
};

