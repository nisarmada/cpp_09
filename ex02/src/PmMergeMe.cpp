#include "../include/PmergeMe.hpp"


PmMergeMe::PmMergeMe() {}

PmMergeMe::PmMergeMe(const std::vector<int>& sequence) : _vector(sequence) {}

PmMergeMe::~PmMergeMe() {}

PmMergeMe::PmMergeMe(const PmMergeMe& other) : _vector(other._vector) {}

PmMergeMe& PmMergeMe::operator=(const PmMergeMe& other) {
	if (this != &other) {
		_vector = other._vector;
	}
	return (*this);
}

void runPmMerge(char* av[]) {
	try {
		checkInput(av);
		std::vector<int> unsortedVector = convertToVector(av);
		printVector(unsortedVector);
		PmMergeMe object(unsortedVector);
	}
	catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

