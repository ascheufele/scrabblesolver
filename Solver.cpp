#include <iostream>
#include "Solver.hpp"
#include <fstream>
using namespace std;

void recur(char arr[], string out, int i, int n, int k, vector<char*>& combinations);
void HeapPermute(char v[], int n, int original_length, vector<string>& permutations);

Solver::Solver()
{
	//set up larger vector (the dictionary im working with has one 31 letter word)
	for (int a = 0; a < 32; a++)
	{
		vector<string>* v = new vector<string>;
		dictionary.push_back(v);
	}

	//read the dictionary into memory
	string temp;
	ifstream dicIn("dictionary.txt");
	while (!dicIn.fail())
	{
		dicIn >> temp;
		dictionary[temp.length()]->push_back(temp);
		//cout << "Inserted \"" << temp << "\" at position " << temp.length() << endl;
	}

}

void Solver::all_words(char letters[], int size, int word_length)
{
	vector<char*> combinations;
	vector<string> permutations;
	vector<string>* working_vector = dictionary[word_length];
	vector<string> solutions;

	//generate all possible combinations
	cout << "Generating combinations..." << endl << endl;;
	recur(letters, "", 0, size, word_length, combinations);
	cout << "There are " << combinations.size() << " unique combinations..." << endl << endl;
	cout << "Generating permutations, and checking if they are in the dictionary.." << endl << endl;
	for (int a = 0; a < combinations.size(); a++)
	{
		//generate permutations
		HeapPermute(combinations[a], word_length, word_length, permutations);
		//check if theyre in the dictionary
		for (auto i = working_vector->begin(); i != working_vector->end(); i++)
		{
			for (auto j = permutations.begin(); j != permutations.end(); j++)
			{
				//if they are add them to solution vector if they are new
				if (*i == *j)
				{
					if (!count(solutions.begin(), solutions.end(), (*j)))
					{
						solutions.push_back((*j));
					}
				}
			}
		}
	}

	cout << "The final list of " << word_length << " letter words is..." << endl << endl;
	for (auto a = solutions.begin(); a != solutions.end(); a++)
	{
		cout << *a << endl;
	}
	cout << endl <<"Thank you for using my tool." << endl;

	for (int a = 0; a < combinations.size(); a++)
	{
		delete combinations[a];
	}
}

Solver::~Solver()
{
	for (int a = 0; a < 32; a++)
	{
		delete dictionary[a];
	}
}

void HeapPermute(char v[], int n, int original_length, vector<string>& permutations)
{
	int i;
	// Print the sequence if the heap top reaches to the 1.
	if (n == 1)
	{
		string word = "";
		for (int a = 0; a < original_length; a++)
		{
			word += v[a];
			//cout << (int)v[a] << " ";
		}
		//cout << word << endl;
		permutations.push_back(word);
	}
	else
	{
		// Fix a number at the heap top until only two one element remaining and permute remaining.
		for (i = 0; i < n; i++)
		{
			HeapPermute(v, n - 1, original_length, permutations);
			// If odd then swap the value at the start index with the n-1.
			if (n % 2 == 1)
				swap(v[0], v[n - 1]);
			// If even then swap the value at the 'i' index with the n-1.
			else
				swap(v[i], v[n - 1]);
		}
	}
}

// Function to print all distinct combinations of length k
void recur(char arr[], string out, int i, int n, int k, vector<char*>& combinations)
{
	// invalid input
	if (k > n)
		return;

	// base case: combination size is k
	if (k == 0) {
		//cout << out << endl;
		//put out into a char array and add it to the combination vector
		char* pArr = new char[out.length()];
		for (int a = 0; a < out.length(); a++)
		{
			pArr[a] = out[a];
		}
		combinations.push_back(pArr);
		
		return;
	}

	// start from next index till last index
	for (int j = i; j < n; j++)
	{
		// add current element arr[j] to solution & recur for next index
		// (j+1) with one less element (k-1)
		recur(arr, out + "" + arr[j], j + 1, n, k - 1, combinations);

		// uncomment below code to handle duplicates
		while (j < n - 1 && arr[j] == arr[j + 1])
			j++;
	}
}