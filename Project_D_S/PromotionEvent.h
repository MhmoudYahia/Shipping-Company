#pragma once
#include"Event.h"
#include"Cargo.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
class PromotionEvent :public Event
{
	int ExtraMoney;
public:
	PromotionEvent(Time ET, int ID, int exm);
	void setExtraMoney(int exm);
	int getExtraMoney();
	virtual void Execute(Cargo * C);
};

