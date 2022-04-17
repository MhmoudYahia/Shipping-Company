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
	Mode M;
	cout << "if you want interactive or step-by-step or silent mode write 0 or 1 or 2 respectively\n";
		cin >> i;
		if (i == 0)M = interactive;
		else if (i == 1)M = step_by_step;
		else if (i == 2)M = silent;
		else cout << "NOT VALID\n";
		return M;
}

void UIClass::PrintCurrentTime(pair<int, int> p)
{
	cout << "Current Time (Day:Hour):" << p.first << ":" << p.second << endl;
}
