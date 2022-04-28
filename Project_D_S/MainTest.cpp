#include<iostream>
#include"PriorityQueue.h"
#include"Queue.h"
#include"UIClass.h"
#include "Company.h"
using namespace std;

//void Printd(PriorityQueue<int>q) {
//	int a;
//	while (q.dequeue(a)) {
//		cout << a << " ";
//	}
//	cout << endl;
//}
int main() {
	Company* CompanyTest = new Company;
	CompanyTest->Loading_File();
	CompanyTest->GeneralSimulate();
	CompanyTest->PrintEvents();
	//PriorityQueue<Cargo*>priQ;
	//Cargo* c2 = new VIPCargo();
	//c2->SetID(10);
	//Cargo* c3 = new NormalCargo();
	//c3->SetID(6);
	//Cargo* c4 = new SpecialCargo();
	//c4->SetID(5);
	//Cargo* c1 = new VIPCargo();
	//c1->SetID(4);
	//priQ.enqueue(c2, c2->Getpriority());
	//priQ.enqueue(c1, c1->Getpriority());
	//priQ.enqueue(c3, c3->Getpriority());
	//priQ.enqueue(c4, c4->Getpriority());
	///*Cargo* ptr;
	//priQ.dequeue(ptr);

	//Printd(priQ);*/
	//UIClass* UI = new UIClass();

	//UI->printWaitingCargos(priQ);
		return 0;
}
