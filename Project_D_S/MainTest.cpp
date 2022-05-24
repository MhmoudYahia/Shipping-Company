#include<iostream>
#include"PriorityQueue.h"
#include"Queue.h"
#include"UIClass.h"
#include "Company.h"
#include"List.h"
using namespace std;

int main() {
	Company* CompanyTest = new Company;
	/*CompanyTest->Loading_File();
	CompanyTest->CreateTrucks();
	CompanyTest->GeneralSimulate();*/
	CompanyTest->TestAll();
	/*List<Cargo*>L;
	Cargo *c1= new Cargo();
	c1->SetID(1);
	Cargo* c2 = new Cargo();
	c2->SetID(2);
	Cargo* c4 = new Cargo();
	c4->SetID(4);
	Cargo* c3 = new Cargo();
	c3->SetID(3);
	
	L.InsertEnd(c1);
	L.InsertEnd(c2);
	L.InsertEnd(c3);
	L.InsertEnd(c4);
	Cargo* Cpr;
	cout << L.GetCount() << endl;
	L.PrintL(u);
	cout << endl;
	L.DeleteFirst(Cpr);
    cout << Cpr->GetID()<<endl;
	L.PrintL(u);
	L.Remove(4);
	cout << endl;
	L.PrintL(u);
	cout << endl;
	cout<<(L.PointerToNormalCRGO(2))->getitem()->GetID();*/
	/*UIClass* u = new UIClass();
	Queue<int>q;
	q.enqueue(5);
	q.enqueue(6);
	q.enqueue(7);
	cout << endl;
	q.PrintQ(u);*/
		return 0;
}
