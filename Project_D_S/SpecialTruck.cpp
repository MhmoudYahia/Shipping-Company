#include "SpecialTruck.h"
#include "Truck.h"

void SpecialTruck::Print(UIClass* UI) {
	cout << "(";
	TruckCargos.Print(UI);
	cout << ")";
}