#include <iostream>
#include "dynlist.h"
#include <string>
#include <vector>

int main() {
	const int size = 10;
	dynlist<char> m1(size), m2(size);
	for (int i = 0; i < m1.len(); i++)
		m1[i] = 1 + rand() % 100;

	std::cout << false ? m1 == m2 : true;


	return 0;
}