#pragma once
#include "Cargo.h"
#include"Queue.h"
#include"Stack.h"

class NormalCargo :public Cargo
{
public:
    NormalCargo() {}
	template<class T>
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
		while (!temp->iSempty())
		{
			t = temp->dequeue(tocancel);
			t = ptr->enqueue(tocancel);
		}
			
		if (DONE)
			return true;
		return false;
	}
    ~NormalCargo(){}
};

