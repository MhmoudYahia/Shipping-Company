#include "UIClass.h"
#include "Queue.h"
#include "NormalTruck.h"
#include "VIPTruck.h"
#include "SpecialTruck.h"
template<class T>
class Queue;
class Truck;
UIClass::UIClass()
{
}

UIClass::~UIClass()
{
}

void UIClass::getKey()
{
	string s;
	cout <<"\nenter any key to continue\n";
	cin >> s;
}

Mode UIClass::SelectMode()
{
	int i;
	//Mode M;//as a default{}{}
	//cout << "if you want interactive or step-by-step or silent mode write 0 or 1 or 2 respectively\n";
	cout << "choose what you want\n0=====>iteractive mode\n1=====>stepBystep mode\n2=====>silent mode\n";
	cin >> i;
		if (i == 0)
			return interactive;
		else if (i == 1)
			return step_by_step;
		else if (i == 2)
			return silent;
		else cout << "NOT VALID\n";
		
}

void UIClass::PrintLine()
{
	cout << "\n---------------------------------------------------------------------\n";
}
template<class t>
void UIClass::Print(t c)
{
	cout << c;
}
template<>
void UIClass::Print(Cargo*c)
{
	cout << c->GetID();
}
template<>
void UIClass::Print(Truck* t)
{
	cout << t->GetID();
}

void UIClass::PrintCurrentTime(Time T)
{
	cout << "\nCurrent Time (Day:Hour):" << T.getDAY() << ":" << T.gethour() << endl;
}
void UIClass::printWaitingCargos(PriorityQueue<Cargo*> qWc)
{
	///*List<Cargo*>l;
	//for (auto it : l) {

	//}*/
	cout << qWc.GetCount()<<" Waiting Cargo: ";
	//Queue<Cargo*>tempQ{};
	Queue<Cargo*>vipQ;
	Queue<Cargo*>spQ;
	Queue<Cargo*>nrmQ;
	Cargo* Cptr=nullptr;
	while (qWc.dequeue(Cptr)) {

		//	tempQ.enqueue(Cptr);
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
	//	while (tempQ.dequeue(Cptr))
			//qWc->enqueue(Cptr, Cptr->Getpriority());
	}
		//printing normal
		if (nrmQ.GetCount() > 0) {
			cout << '[';
			nrmQ.PrintQ(this);
			//PrintQ(nrmQ);
			cout << "] ";
		}
		//printing special
		if (spQ.GetCount() > 0) {
			cout << '(';
			spQ.PrintQ(this);
			//PrintQ(spQ);
			cout << ") ";
		}
		//printing vip
		if (vipQ.GetCount() > 0) {
			cout << '{';
			vipQ.PrintQ(this);
			//PrintQ(vipQ);
			cout << "} ";
		}
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


void UIClass::PrintMovingCargos(Queue<Cargo*> qMc)//phase 2
{

}

void UIClass::PrintDeliveredCargo(Queue<Cargo*>qDc)
{
	cout << qDc.GetCount() << " Delivered Cargo: ";
	//Queue<Cargo*>tempQ{};
	Queue<Cargo*>vipQ;
	Queue<Cargo*>spQ;
	Queue<Cargo*>nrmQ;
	Cargo* Cptr;
	while (!qDc.isEmpty()) {
		qDc.dequeue(Cptr);
		//tempQ.enqueue(Cptr);
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
	///	while (tempQ.dequeue(Cptr))
		///	qDc->enqueue(Cptr);


		//printing vip
		if (vipQ.GetCount() > 0) {
			cout << '{';
			vipQ.PrintQ(this);
			//PrintQ(vipQ);
			cout << "} ";
		}
		//normal
		if (nrmQ.GetCount() > 0) {
			cout << '[';
			nrmQ.PrintQ(this);
			//PrintQ(nrmQ);
			cout << "] ";
		}
		//printing special
		if (spQ.GetCount() > 0) {
			cout << '(';
			spQ.PrintQ(this);
			//PrintQ(spQ);
			cout << ") ";
		}
	}
}



void UIClass::PrintIn_CheckupTrucks(Queue<Truck*> qCt)
{
	cout << qCt.GetCount() << " In_CheckupTrucks: ";
	//	Queue<Truck*>tempQ{};
	Queue<Truck*>vipQ;
	Queue<Truck*>spQ;
	Queue<Truck*>nrmQ;
	Truck* Cptr;
	while (!qCt.isEmpty()) {
		qCt.dequeue(Cptr);
		//	tempQ.enqueue(Cptr);
		if (dynamic_cast<NormalTruck*>(Cptr)) {
			nrmQ.enqueue(Cptr);
		}
		if (dynamic_cast<VIPTruck*>(Cptr)) {
			vipQ.enqueue(Cptr);
		}
		if (dynamic_cast<SpecialTruck*>(Cptr)) {
			spQ.enqueue(Cptr);
		}
	}
	//return origin qDl
	/*while (tempQ.dequeue(Cptr))
		qCt->enqueue(Cptr);*/
		//printing normal
	if (nrmQ.GetCount() > 0)
	{
		cout << '[';
		nrmQ.PrintQ(this);
		//PrintQ(nrmQ);
		cout << "] ";
	}
	//printing special
	if (spQ.GetCount()>0) {
		cout << '(';
		spQ.PrintQ(this);
	//	PrintQ(spQ);
		cout << ") ";
	}

	//printing vip
	if (vipQ.GetCount() > 0) {
		cout << '{';
		vipQ.PrintQ(this);
		//PrintQ(vipQ);
		cout << "} ";
	}
}

void UIClass::PrintEmptytrucks(Queue<Truck*>qEt)
{
	cout << qEt.GetCount() << " Empty Trucks: ";
//	Queue<Truck*>tempQ;
	Truck* Cptr;
	while (qEt.GetCount()>1) {
		qEt.dequeue(Cptr);
	//tempQ.enqueue(Cptr);
		if (dynamic_cast<NormalTruck*>(Cptr)) {
			cout << " [" << Cptr->GetID() << "],";
		}
		if (dynamic_cast<VIPTruck*>(Cptr)) {
			cout << " {" << Cptr->GetID() << "},";
		}
		if (dynamic_cast<SpecialTruck*>(Cptr)) {
			cout << " (" << Cptr->GetID() << "),";
		}
	}
	//as we do not want ',' to appear in last printing op.
	if (qEt.dequeue(Cptr)) {   
//	tempQ.enqueue(Cptr);
		if (dynamic_cast<NormalTruck*>(Cptr)) {
			cout << " [" << Cptr->GetID() << "]";
		}
		else if (dynamic_cast<VIPTruck*>(Cptr)) {
			cout << " {" << Cptr->GetID() << "}";
		}
		else if (dynamic_cast<SpecialTruck*>(Cptr)) {
			cout << " (" << Cptr->GetID() << ")";
		}
	}
	//return origin qEl
	/*while (tempQ.dequeue(Cptr))
		qEt->enqueue(Cptr);*/
}

void UIClass::PrintLoadingTrucks(Queue<Truck*> qLt)
{
	cout << qLt.GetCount() << " LoadingTrucks: ";
//	Queue<Truck*>tempQ;
	Truck* Cptr;
	while (qLt.dequeue(Cptr)) {
		//tempQ.enqueue(Cptr);
		if (dynamic_cast<NormalTruck*>(Cptr)) {
			cout << Cptr->GetID() << "[";
			Cptr->Print(this);
			cout << "] ";
		}
		if (dynamic_cast<VIPTruck*>(Cptr)) {
			cout << Cptr->GetID() << "{";
			Cptr->Print(this);
			cout << "} ";
		}
		if (dynamic_cast<SpecialTruck*>(Cptr)) {
			cout << Cptr->GetID() << "(";
			Cptr->Print(this);
			cout << ") ";
		}
	}
	//return origin qLt
	//while (tempQ.dequeue(Cptr))
		//qLt->enqueue(Cptr);
}

void UIClass::PrintSilentMode()
{
	cout << "SilentMode\n" << "Simulation Starts...\n" << "Simulation ends, Output file created\n";
}

void UIClass::PrintError(string msg) {
	cout << "Error: " << msg << endl;
}
//void UIClass::PrintQ(Queue<Cargo*  > Cptr) {
//	Cargo* C;
//	while (Cptr.dequeue(C) && Cptr.GetCount() != 1) {
//		Print(C);
//		cout<< ',';
//	}
//	if (Cptr.dequeue(C));
//	Print(C);
//}
//void UIClass::PrintQ(Queue<Truck*  > Cptr) {
//	Truck* C;
//	while (Cptr.dequeue(C) && Cptr.GetCount() != 1) {
//		Print(C);
//		cout << ',';
//	}
//	if (Cptr.dequeue(C));
//	Print(C);
//}
