#include "NormalTruck.h"
#include "Truck.h"
void NormalTruck::Print(UIClass* UI) {
	cout << "[";
	TruckCargos.Print(UI);
	cout << "]";
}