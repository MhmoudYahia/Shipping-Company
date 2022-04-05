#include<iostream>
#include"PriorityQueue.h"
#include"Queue.h"
using namespace std;
int main() {
	PriorityQueue<int>q1;
	q1.enqueue(5, 5);
	q1.enqueue(6,7 );
	q1.enqueue(4, 4);
	q1.enqueue(2, 8);
	int x;
	while (q1.dequeue(x))
		cout << x << " ";
	return 0;
}