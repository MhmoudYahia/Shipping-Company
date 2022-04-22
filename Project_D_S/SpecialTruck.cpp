#include "SpecialTruck.h"
#include "Truck.h"

void SpecialTruck::Print(UIClass* UI) {
	cout << "[";
	Truck::Print(UI);
	cout << "]";
}