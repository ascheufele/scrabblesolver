#include <iostream>
#include "Solver.hpp"
using namespace std;

int main(void)
{
	char letters[] = { 'e', 'c', 'c', 'i', 'h', 't'};

	Solver test;
	test.all_words(letters, 6, 5);

	return 0;
}