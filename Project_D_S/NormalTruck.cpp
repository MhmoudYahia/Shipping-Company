#include "NormalTruck.h"
#include "Truck.h"
void NormalTruck::Print(UIClass* UI) {
	cout << "[";
	Truck::Print(UI);
	cout << "]";
}