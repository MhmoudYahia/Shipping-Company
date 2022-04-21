#include "UIClass.h"

UIClass::UIClass()
{
}

UIClass::~UIClass()
{
}

void UIClass::getKey()
{
	string s;
	cin >> s;
}

Mode UIClass::SelectMode()
{
	int i;
	//Mode M;//as a default{}{}
	cout << "if you want interactive or step-by-step or silent mode write 0 or 1 or 2 respectively\n";
		cin >> i;
		if (i == 0)
			return interactive;
		else if (i == 1)
			return step_by_step;
		else if (i == 2)
			return silent;
		else cout << "NOT VALID\n";
		
}

void UIClass::PrintID(Cargo*c)
{
	cout << c->GetID();
}

void UIClass::PrintID(Truck* t)
{
	cout << t->GetID();
}

void UIClass::PrintCurrentTime(pair<int, int> p)
{
	cout << "Current Time (Day:Hour):" << p.first << ":" << p.second << endl;
}

void UIClass::printWaitingCargos(PriorityQueue<Cargo*>* qWc)
{
	cout << qWc->GetCount()<<" Waiting Cargo: ";
	Queue<Cargo*>tempQ{};
	Queue<Cargo*>vipQ;
	Queue<Cargo*>spQ;
	Queue<Cargo*>nrmQ;
	Cargo* Cptr;
	while (!qWc->iSempty()) {
		qWc->dequeue(Cptr);
		tempQ.enqueue(Cptr);
		if (dynamic_cast<NormalCargo*>(Cptr)) {
			nrmQ.enqueue(Cptr);
		}
		if (dynamic_cast<VIPCargo*>(Cptr)) {
			vipQ.enqueue(Cptr);
		}
		if (dynamic_cast<SpecialCargo*>(Cptr)) {
			spQ.enqueue(Cptr);
		}
		//return origin qWl
		while (tempQ.dequeue(Cptr))
			qWc->enqueue(Cptr,Cptr->Getpriority());

		//printing normal
		cout << '[';
		nrmQ.Print(this);
		cout  << '] ';

		//printing special
		cout << '(';
		spQ.Print(this);
		cout << ') ';

		//printing vip
		cout << '{';
		vipQ.Print(this);
		cout <<'} ';
	}
	/*while (nrmQ.dequeue(Cptr)&&nrmQ.GetCount()!=1)
		cout << Cptr->GetID() << ',';
	if(nrmQ.dequeue(Cptr));*/
	/*while (vipQ.dequeue(Cptr) && vipQ.GetCount() != 1)
			cout << Cptr->GetID() << ',';
		if (vipQ.dequeue(Cptr));*/
		/*while (spQ.dequeue(Cptr) && spQ.GetCount() != 1)
				cout << Cptr->GetID() << ',';
			if (spQ.dequeue(Cptr));*/
}

void UIClass::PrintMovingCargos(Queue<Cargo*>* qMc)
{

}

void UIClass::printDeliveredCargo(Queue<Cargo*>* qDc)
{
	cout << qDc->GetCount() << " Delivered Cargo: ";
	Queue<Cargo*>tempQ{};
	Queue<Cargo*>vipQ;
	Queue<Cargo*>spQ;
	Queue<Cargo*>nrmQ;
	Cargo* Cptr;
	while (!qDc->iSempty()) {
		qDc->dequeue(Cptr);
		tempQ.enqueue(Cptr);
		if (dynamic_cast<NormalCargo*>(Cptr)) {
			nrmQ.enqueue(Cptr);
		}
		if (dynamic_cast<VIPCargo*>(Cptr)) {
			vipQ.enqueue(Cptr);
		}
		if (dynamic_cast<SpecialCargo*>(Cptr)) {
			spQ.enqueue(Cptr);
		}

		//return origin qDl
		while (tempQ.dequeue(Cptr))
			qDc->enqueue(Cptr);


		//printing vip
		cout << '{';
		vipQ.Print(this);
		cout << '} ';

		//printing normal
		cout << '[';
		nrmQ.Print(this);
		cout << '] ';

		//printing special
		cout << '(';
		spQ.Print(this);
		cout << ') ';
	}
}

void UIClass::PrintIn_CheckupTrucks(Queue<Cargo*>* qCt)
{

}


