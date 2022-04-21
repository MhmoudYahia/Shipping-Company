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

void UIClass::PrintCurrentTime(pair<int, int> p)
{
	cout << "Current Time (Day:Hour):" << p.first << ":" << p.second << endl;
}

void UIClass::printWaitingCargos(PriorityQueue<Cargo*>* qWc)
{
	Cargo* Cptr;
	while (!qWc->iSempty()) {

	}
}


