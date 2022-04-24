#pragma once
#include"Event.h"
#include"Cargo.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
class PromotionEvent :public Event
{
	int ExtraMoney;
	VIPCargo* VCargoptr;
public:
	PromotionEvent(Time ET, int ID, int ex, NormalCargo*);
	void setExtraMoney(int exm);
	int getExtraMoney();
	NormalCargo* NCargoptr;
	VIPCargo* getVIPCargo();
	NormalCargo* getNormalCargo();
	virtual void Execute();
};

