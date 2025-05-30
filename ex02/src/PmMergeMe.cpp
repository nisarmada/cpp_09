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

// static void printBlock(const std::vector<int>& data, size_t currentBlockSize, size_t current_i, int level) {
//     std::cout << "Level " << level << " (Block Size " << currentBlockSize << "): [";
//     for (size_t k = 0; k < data.size(); ++k) {
//         // Mark the start of a block
//         if (k > 0 && k % currentBlockSize == 0 && k % (2 * currentBlockSize) != 0) {
//             std::cout << " | "; // Separator between blocks within a pair
//         } else if (k > 0 && k % (2 * currentBlockSize) == 0) {
//             std::cout << " || "; // Separator between pairs of blocks
//         }

//         // Highlight the current pair of blocks being processed by the loop 'current_i'
//         if (k == current_i) {
//             std::cout << "<"; // Start of the first block in the current pair
//         } else if (k == current_i + currentBlockSize) {
//             std::cout << "["; // Start of the second block in the current pair
//         }

//         std::cout << data[k];

//         // Highlight the end of the current pair of blocks
//         if (k == current_i + currentBlockSize - 1) {
//             std::cout << ">"; // End of the first block in the current pair
//         } else if (k == std::min(current_i + 2 * currentBlockSize, data.size()) - 1) {
//              // This is tricky: it's the last element of the second block, or the last element of the vector
//              // if the second block is truncated.
//              if (current_i + currentBlockSize < data.size()) { // Only if there's a second block
//                  std::cout << "]"; // End of the second block in the current pair
//              }
//         }

//         if (k < data.size() - 1) {
//             std::cout << " ";
//         }
//     }
//     std::cout << "]" << std::endl;
// }

void PmMergeMe::recursiveSort(std::vector<int>& data, size_t blockSize, int level){
	if (blockSize * 2 > data.size())
		return ;
	recursiveSort(data, blockSize * 2, level + 1);
	std::cout << "We are at level " << level << " of recursion" << std::endl;
	for (int i = 0; i + blockSize < data.size(); i += 2 * blockSize) {
		// int block1start = i;
		int block1end = i + blockSize - 1;
		// int block2start = i + blockSize;
		int block2end = std::min(i + 2 * blockSize - 1, data.size() - 1);
		//I might need to check if (block2start <= data.size()) if my code doesn't work this way
		std::cout << "BEFORE LEVEL " << level << " BLOCKSIZE " << blockSize << std::endl;
		printVector(data, blockSize);
		// printBlock(data, blockSize, i, level);
		if (data[block1end] > data[block2end])
			std::rotate(data.begin() + i, data.begin() + i + blockSize, data.begin() + block2end + 1);
		std::cout << "AFTER LEVEL " << level << " BLOCKSIZE " << blockSize << std::endl;
		printVector(data, blockSize);

	}
}

void PmMergeMe::sortAndDisplayResults() {
	std::vector<int> tempVector = _vector;

	if (tempVector.size() % 2 != 0) {
		_oddElement = tempVector.back();
		tempVector.pop_back();
	}
	recursiveSort(tempVector, 1);
	std::vector<int> mainChain;
	std::vector<int> pend;

	for (size_t i = 0; i < tempVector.size(); i += 2) {
		mainChain.push_back(tempVector[i + 1]);
		pend.push_back(tempVector[i]);
	}
	std::cout << "main chain" << std::endl;
	printVector(mainChain, 0);
	std::cout << "Pend" << std::endl;
	printVector(pend, 0);
	
}

void runPmMerge(char* av[]) {
	try {
		checkInput(av);
		std::vector<int> unsortedVector = convertToVector(av);
		// printVector(unsortedVector, static_cast<size_t>0);
		PmMergeMe object(unsortedVector);
		object.sortAndDisplayResults();
	}
	catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

