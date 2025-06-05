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

std::vector<int> PmMergeMe::generateJacobsthal(int n) {
	if (n <= 1) {
		return {};
	}
	std::vector<int> jacobsthalNumbers;
	if (n > 1) {
		jacobsthalNumbers.push_back(0);
		jacobsthalNumbers.push_back(1);
	}
	while (jacobsthalNumbers.back() <= n) {
		int nextJacobsthal = jacobsthalNumbers[jacobsthalNumbers.size() - 1] + 2 * jacobsthalNumbers[jacobsthalNumbers.size() - 2];
		jacobsthalNumbers.push_back(nextJacobsthal);
	}
	//check if we generate extra numbers that exceed n, we might need to delete the last one
	return jacobsthalNumbers;
}

void PmMergeMe::recursiveInsertion(std::vector<int>& partiallySortedVector, size_t blockSize) {
	if (blockSize == 1)
		return ;
	std::vector<int> main;
	std::vector<int> pend;
	std::vector<int> remaining;
	bool isMain = true;
	size_t i;
	std::cout << "block size is " << blockSize << std::endl;
	for (i = 0; i < 2 * blockSize; i++) { //a1
		main.push_back(partiallySortedVector[i]);
		// std::cout << "a1: " << partiallySortedVector[i] << std::endl;
	}
	if (i + blockSize <= partiallySortedVector.size()) {
		for (size_t j = 0; j < blockSize; j++) {
			pend.push_back(partiallySortedVector[i++]);
		}
	}
	while (i < partiallySortedVector.size()) {
		// size_t steps = 0;
		if (i + blockSize <= partiallySortedVector.size()) {
			if (isMain) {
				for (size_t j = 0; j < blockSize; j++) {
					main.push_back(partiallySortedVector[i]);
					i++;
					// steps++;
				}
			}
			else{
				for (size_t j = 0; j < blockSize; j++) {
					pend.push_back(partiallySortedVector[i]);
					i++;
					// steps++;
				}
			}
		}
		else {
			break;
		}
		isMain = !isMain;
		// std::cout << "PPPPPPPPi: " << i << "size: " << partiallySortedVector.size() << std::endl;

	}
	std::cout << "main: ";
	printVector(main, blockSize);
	std::cout << std::endl;
	std::cout << "pend: ";
	printVector(pend, blockSize);
	std::cout << std::endl;
	while (i < partiallySortedVector.size()) {
		remaining.push_back(partiallySortedVector[i]);
		i++;
	}
	std::cout << "remaining: ";
	printVector(remaining, blockSize);
	std::cout << std::endl;
	size_t pendBlocks = pend.size() / blockSize;
	int previousJacobsthal = 1;
	int pendCount = 0;
	std::vector<int> insertOrder;
	std::vector<int> jacbobsthalSequence = generateJacobsthal(pendBlocks);
	if (jacbobsthalSequence.size() > 2) {
		int currentJacobsthal = jacbobsthalSequence[2];
		int startBlock = std::min(currentJacobsthal, static_cast<int>(pendBlocks));
		int endBlock = previousJacobsthal + 1;

		for (int i = startBlock; i >= endBlock && i > pendCount; --i) {
			insertOrder.push_back((i - 1) * blockSize);
		}
		previousJacobsthal = currentJacobsthal;
		pendCount = startBlock;
	}
	recursiveInsertion(partiallySortedVector, blockSize / 2);
}


void PmMergeMe::recursiveSort(std::vector<int>& data, size_t blockSize, int level){
	if (blockSize * 2 > data.size()) {
		// std::cout << "level-> " << level << std::endl;
		recursiveInsertion(data, blockSize / 2);
		return ;
	} // here we can add the insertion recursively
	// std::cout << "BEFORE LEVEL " << level << std::endl; 
	for (size_t i = 0; i + (2 *blockSize) <= data.size(); i += 2 * blockSize) {
		size_t block1end = i + blockSize - 1;
		size_t block2end = std::min(i + 2 * blockSize - 1, data.size() - 1);
		// printVector(data, blockSize);
		if (level == 1 && data[block1end] > data[block2end]) {
				std::swap(data[block1end], data[block2end]);
		}
		else if (data[block1end] > data[block2end]) {
			// std::cout << "COMPARING " << data[block1end] << " WITH " << data[block2end] << std::endl;
			std::rotate(data.begin() + i, data.begin() + i + blockSize, data.begin() + block2end + 1);
		}
		
	}
	// std::cout << "AFTER LEVEL " << level << std::endl; 
	printVector(data, blockSize);
	recursiveSort(data, 2 * blockSize, level + 1);
}

void PmMergeMe::sortAndDisplayResults() {
	std::vector<int> tempVector = _vector;

	if (tempVector.size() % 2 != 0) {
		_oddElement = tempVector.back();
		tempVector.pop_back();
	}
	recursiveSort(tempVector, 1);
	// std::cout << "YPPPP" << std::endl;
	// printVector(tempVector);
}

void runPmMerge(char* av[]) {
	try {
		checkInput(av);
		std::vector<int> unsortedVector = convertToVector(av);
		PmMergeMe object(unsortedVector);
		object.sortAndDisplayResults();
	}
	catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

