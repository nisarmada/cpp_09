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
		void recursiveSort(std::vector<int>& initialVector, size_t blockSize, int level = 1);
		void recursiveInsertion(std::vector<int>& partiallySortedVector, size_t blockSize);
		int _oddElement = -1;
	public:
		PmMergeMe();
		PmMergeMe(const std::vector<int>& sequence);
		~PmMergeMe();

		PmMergeMe(const PmMergeMe& other);
		PmMergeMe& operator=(const PmMergeMe& other);

		void sortAndDisplayResults();
		std::vector<int> generateJacobsthal(int n);
};

void runPmMerge(char* av[]);
void printVector(std::vector<int>& vector, size_t blockSize = 0);
void checkInput(char* av[]);
std::vector<int> convertToVector(char* av[]);