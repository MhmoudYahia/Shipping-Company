#include "VIPCargo.h"

VIPCargo::VIPCargo()
{
	Priority = 0;
}
VIPCargo::VIPCargo(int ID, double P, int d, int h, double lt, double c, int dis) {
	SetID(ID);
	Priority = P;
	UpdatePriority();
	setPT(d, h);
	SetLT(lt);
	SetDis(dis);
	SetCost(c);

}

int VIPCargo::Getpriority()
{
	return Priority;
}

void VIPCargo::UpdatePriority()
{
	if (Per_T.getDAY() != 0 && Per_T.gethour() != 0) {
		Priority = cost + delvr_Dis + 1.0 / (Per_T.getDAY() + Per_T.gethour());
	}
}

void VIPCargo::setPT(int d, int h)
{
	this->Per_T.first = (d > 0) ? d : 0;
	this->Per_T.second = (h >= 0 && h < 24) ? h : 0;
	UpdatePriority();
}

void VIPCargo::SetLT(double t)
{
	this->Load_T = (t > 0) ? t : 0;
	UpdatePriority();

}

void VIPCargo::SetDis(double d)
{
	this->delvr_Dis = (d > 0) ? d : 0;
	UpdatePriority();

}

void VIPCargo::SetCost(double c)
{
	this->cost = (c > 0) ? c : 0;
	UpdatePriority();

}

VIPCargo::~VIPCargo()
{
}
