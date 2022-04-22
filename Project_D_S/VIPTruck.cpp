#include "VIPTruck.h"
void NormalTruck::Print(UIClass* UI) {
	cout << "[";
	Truck::Print(UI);
	cout << "]";
}