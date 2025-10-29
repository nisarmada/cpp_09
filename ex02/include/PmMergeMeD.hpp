#pragma once

#include "PmMergeMe.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <exception>
#include <vector>
#include <deque>

struct s_element;

class PmMergeMeD {
	private:
		std::deque<int> _deque;
		int _oddElement = -1;

	public:
		PmMergeMeD();
		PmMergeMeD(const std::deque<int>& sequence);
		~PmMergeMeD();

		PmMergeMeD(const PmMergeMeD& other);
		PmMergeMeD& operator=(const PmMergeMeD& other);
		
		void sortAndDisplayResults();
		void addOddElement(std::deque<int>& main);
		
		void performMergeInsertion(std::deque<int>& deque);
		std::deque<element> assignNumberPairs(std::deque<int>& deque);
		std::deque<element> recursivelySortElements(std::deque<element>& pairedDeque);
		void insertElements(std::deque<element>& main, std::deque<element>& pend);
		void performBinarySearch(std::deque<element>& main, element& elementToInsert);
		int findPair(std::deque<element>& main, element& elementToInsert);


};

std::deque<int> convertToDeque(char* av[]);
void printDeque(std::vector<int>& deque, size_t blockSize);
void printElementDeque(std::deque<element>& deque);