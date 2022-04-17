#pragma once
#include<iostream>
using namespace std;
#include<string>
#include"PriorityQueue.h"
#include"Queue.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
#include"SpecialCargo.h"


enum Mode { interactive, step_by_step, silent };
class UIClass
	
{
public:
	UIClass();
	~UIClass();
	void getKey();
	Mode SelectMode();
	void PrintCurrentTime(pair<int, int>p);
	void interactiveExcute();//waiting for company

};

