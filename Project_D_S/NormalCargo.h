#pragma once
#include "Cargo.h"
#include"Stack.h"
template<class T>
class Queue;
class NormalCargo :public Cargo
{
public:
    NormalCargo() {}
	/*template<class T>
	bool N_Cargo_Cancellation(Queue<T>* ptr,int id)
	{
		T tem;
		ptr = ptr->front;
		NormalCargo* tocancel;
		Queue<T>* temp=new Queue<T>;
		bool t, DONE;
		while (ptr!=ptr->rear->getnext())
		{
			t=ptr->dequeue(tocancel);
			if (tocancel->GetID() == id)
			{
				delete tocancel;
				tocancel = NULL;
				DONE = true;
			}
			else
			{
				t=temp->enqueue(tocancel);
			}
		}
		while (!temp->isEmpty())
		{
			t = temp->dequeue(tocancel);
			t = ptr->enqueue(tocancel);
		}
			
		if (DONE)
			return true;
		return false;
	}*/
	NormalCargo(int cost, int LT, int DIS, int ID, int H, int D) {
		setPT(D, H);
		SetCost(cost);
		SetLT(LT);
		SetDdes(DIS);
		SetID(ID);
	}

    ~NormalCargo(){}
};

