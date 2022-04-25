#pragma once
#include"Cargo.h"
#include"NormalCargo.h"
#include"Stack.h"
#include "Node.h"
#include "Company.h"
class CancellationEvent :public Event
{
public:
	Time ET;
	CancellationEvent(Time ET,int ID, Company * );
	void virtual Execute();
};

