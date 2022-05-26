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
		return 0;
}
