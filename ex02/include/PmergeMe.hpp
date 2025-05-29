#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <exception>
#include <vector>


class PmMergeMe {
	private:
		std::vector<int> _vector;
	public:
		PmMergeMe();
		PmMergeMe(const std::vector<int>& sequence);
		~PmMergeMe();

		PmMergeMe(const PmMergeMe& other);
		PmMergeMe& operator=(const PmMergeMe& other);
};

void runPmMerge(char* av[]);
void printVector(std::vector<int>& vector);
void checkInput(char* av[]);
std::vector<int> convertToVector(char* av[]);