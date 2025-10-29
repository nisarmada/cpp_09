#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <exception>
#include <vector>

typedef struct {
	int number;
	int partner;
	int originalIndex;
} element;

class PmMergeMe {
	private:
		int _oddElement = -1;
		std::vector<int> _vector;
		std::vector<element> assignNumberPairs(std::vector<int>& initialVector);
		void recursiveInsertion(std::vector<int>& partiallySortedVector, size_t blockSize);
		// std::vector<int> calculateInsertOrder(size_t blockSize, size_t blockNumber);
		void performBinarySearch(std::vector<int>& main, std::vector<int>& pend, size_t blockSize);
		void addOddElement(std::vector<int>& main);
	public:
		PmMergeMe();
		PmMergeMe(const std::vector<int>& sequence);
		~PmMergeMe();

		PmMergeMe(const PmMergeMe& other);
		PmMergeMe& operator=(const PmMergeMe& other);

		void sortAndDisplayResults();
		std::vector<int> generateJacobsthal(int n);
		void performMergeInsertion(std::vector<int>& vector);
		std::vector<element> recursivelySortElements(std::vector<element>& pairedVector);
		void insertElements(std::vector<element>& main, std::vector<element>& pend);
		void performBinarySearch(std::vector<element>& main, element& elementToInsert);
		int findPair(std::vector<element>& main, element& elementToInsert);
};

void runPmMerge(char* av[]);
void printVector(std::vector<int>& vector, size_t blockSize = 0);
void printElementVector(std::vector<element>& vector);
void checkInput(char* av[]);
std::vector<int> convertToVector(char* av[]);
