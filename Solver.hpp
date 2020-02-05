#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

class Solver
{
public:
	Solver();
	~Solver();
	void all_words(char letters[], int size, int word_length);

private:
	std::vector<std::vector<std::string>*> dictionary;
};

#endif // !
