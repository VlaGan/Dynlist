#include <iostream>
#include "dynlist.h"

int main() {
	const int size = 100000;
	dynlist<int> mass(size);
	for (int i = 0; i < size; i++)
		*mass[-(i+1)] = 1+rand() % 32768;

	//mass.print();
	mass.sort();
	//mass.print();

	return 0;
}