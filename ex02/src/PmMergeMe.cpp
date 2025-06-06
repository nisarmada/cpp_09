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

// std::vector<int> PmMergeMe::calculateInsertOrder(size_t blockSize, size_t pendBlocks) {
// 	int previousJacobsthal = 1;
// 	int pendCount = 0;
// 	std::vector<int> jacbobsthalSequence = generateJacobsthal(pendBlocks);
// 	std::vector<int> insertOrder;
// 	// std::cout << "Jacobsthal--> " ;
// 	printVector(jacbobsthalSequence);
// 	std::cout << std::endl;
// 	if (jacbobsthalSequence.size() > 2) {
// 		int currentJacobsthal = jacbobsthalSequence[3];
// 		int startBlock = std::min(currentJacobsthal, static_cast<int>(pendBlocks));
// 		int endBlock = previousJacobsthal + 1;
// 		for (int i = startBlock; i >= endBlock && i > pendCount; --i) {
// 			insertOrder.push_back((i - 1) * blockSize);
// 		}
// 		previousJacobsthal = currentJacobsthal;
// 		pendCount = startBlock;
// 	}
// 	return insertOrder;
// }

void PmMergeMe::performBinarySearch(std::vector<int>& main, std::vector<int>& pend, size_t blockSize) {
	if (pend.empty())
		return ;
	size_t amountBlocks = pend.size() / blockSize;
	std::vector<int> jacobsthalnumbers = generateJacobsthal(amountBlocks);
	size_t jcIndex = 3; //J[2]
	size_t previousJacobsthal = 1; // J[1]
	std::vector<int> currentBlock;
	size_t insertedBlocks = 0;
	std::vector<bool> blockIsInserted(amountBlocks, false);
	while (insertedBlocks < amountBlocks) {
		size_t currentJacobsthal = static_cast<size_t>(jacobsthalnumbers[jcIndex]);
		for (size_t k = currentJacobsthal; k > previousJacobsthal; --k) {
			size_t blockIndex = k - 2;
			if (k >= 2 && blockIndex < amountBlocks && !blockIsInserted[blockIndex]) {
				size_t pendIndex = blockIndex * blockSize;
				if (pendIndex < pend.size()) {
					int lastElementPend = pend[pendIndex + blockSize - 1];
					std::vector<int> lastElementsMain;
					for (size_t i = 0; i + blockSize <= main.size(); i += blockSize) {
						lastElementsMain.push_back(main[i] + blockSize - 1);
					}
					auto lastElementsPosition = std::upper_bound(lastElementsMain.begin(), lastElementsMain.end(), lastElementPend);
					int lastElementIndex = std::distance(lastElementsMain.begin(), lastElementsPosition);
					int insertIndex = blockSize * lastElementIndex;
					currentBlock.clear(); //check if we need
					for (size_t i = 0; i < blockSize; i++) {
						currentBlock.push_back(pend[i + pendIndex]);
					}
					main.insert(main.begin() + insertIndex, currentBlock.begin(), currentBlock.end());
					blockIsInserted[blockIndex] = true;
					insertedBlocks++;
					std::cout << "binary search main :-> ";
                    printVector(main);
                    std::cout << std::endl;
				}
			}
		}
				previousJacobsthal = currentJacobsthal;
				jcIndex++;
	}
}

std::vector<int> PmMergeMe::generateJacobsthal(int n) {
	std::vector<int> jacobsthalNumbers;

	jacobsthalNumbers.push_back(0);
	if (n >= 1) {
		jacobsthalNumbers.push_back(1);
	}
	else {
		return jacobsthalNumbers;
	}
	while (jacobsthalNumbers.size() >= 2) {
		long long nextJacobsthalLL = (long long) jacobsthalNumbers[jacobsthalNumbers.size() - 1] + \
			2LL * jacobsthalNumbers[jacobsthalNumbers.size() - 2];
		int nextJacobsthal =static_cast<int>(nextJacobsthalLL);
		if (nextJacobsthal > n) {
			break;
		}
		jacobsthalNumbers.push_back(nextJacobsthal);
	}
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
	// size_t pendBlocks = pend.size() / blockSize;
	// std::vector<int> insertOrder = calculateInsertOrder(blockSize, pendBlocks);
	// std::cout << "Insert orderrr: ";
	// printVector(insertOrder);
	std::cout << std::endl;
	performBinarySearch(main, pend, blockSize);
	for (size_t i = 0; i < remaining.size(); i++) {
		main.push_back(remaining[i]);
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

