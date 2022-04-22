#include "VIPTruck.h"
void NormalTruck::Print(UIClass* UI) {
	cout << "{";
	TruckCargos.Print(UI);
	cout << "}";
}