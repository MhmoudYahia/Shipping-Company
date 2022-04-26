#include<iostream>
#include"PriorityQueue.h"
#include"Queue.h"
#include"UIClass.h"
#include "Company.h"
using namespace std;
int main() {
	Company* CompanyTest = new Company;
	CompanyTest->Loading_File();
	//CompanyTest->GeneralSimulate();
	CompanyTest->PrintEvents();
	
	return 0;
}