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


void PmMergeMe::addOddElement(std::vector<int>& main) {
	auto oddElementPosition = std::lower_bound(main.begin(), main.end(), _oddElement);
	if (oddElementPosition == main.end()) {
		main.push_back(_oddElement);
	}
	else {
		int oddElementPositionIndex = std::distance(main.begin(), oddElementPosition);
		main.insert(main.begin() + oddElementPositionIndex, _oddElement);
	}
	// std::cout << "odd element position " << *lastElement << std::endl;
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


std::vector<element> PmMergeMe::assignNumberPairs(std::vector<int>& vector){
	std::vector<element> pairedVector;
	for (size_t i = 0; i < vector.size(); i++){
		element currentNumber;
		currentNumber.number = vector[i];
		currentNumber.originalIndex = i;
		if (i % 2 == 0){
			currentNumber.partner = vector[i + 1];
		}
		else{
			currentNumber.partner = vector[i - 1];
		}
		pairedVector.push_back(currentNumber);
	}
	printElementVector(pairedVector);
	return pairedVector;
}

void PmMergeMe::insertElements(std::vector<element>& main, std::vector<element>& pend){
	//do we need to check if pend is empty?
	main.insert(main.begin(), pend[0]);
	pend.erase(pend.begin());
	size_t pendSize = pend.size();
	std::vector<int> jacobsthalNumbers = generateJacobsthal(pendSize + 1);
	int previousJacobsthal = jacobsthalNumbers[2];
	for (size_t k = 3; k < jacobsthalNumbers.size(); k++){
		int currentJacobsthal = jacobsthalNumbers[k];
		int startIndex = previousJacobsthal + 1;
		int endIndex = std::min(currentJacobsthal, (int)pendSize);
		// std::cout << "start index "<< startIndex << std::endl;
		// std::cout << "end index" << endIndex << std::endl;
		for (int i = endIndex; i >= startIndex; --i){
			int pendVectorIndex = i - 2;

			printElementVector(pend);
			if (pendVectorIndex >= (int)pendSize || pendVectorIndex < 0){
				// std::cout << "inside continue pend size" << pendSize << std::endl;
				continue;
			}
			
			element elementToInsert = pend[pendVectorIndex];
		}
	}
}

std::vector<element> PmMergeMe::recursivelySortElements(std::vector<element>& pairedVector){
	if (pairedVector.size() == 1){
		return pairedVector;
	}
	std::vector<element> main;
	std::vector<element> pend;
	//I think I am losing one element in the end here
	for (size_t i = 0; i < pairedVector.size(); i += 2){
		if ((i + 1) > pairedVector.size() - 1){
			break; 
		}
		std::cout << "elements " << pairedVector[i].number << " -- " << pairedVector[i + 1].number << std::endl;
		if (pairedVector[i].number > pairedVector[i + 1].number){
			main.push_back(pairedVector[i]);
			pend.push_back(pairedVector[i + 1]);
		} else {
			main.push_back(pairedVector[i + 1]);
			pend.push_back(pairedVector[i]);
		}
	}
	std::cout << "size is ---> " << pairedVector.size() << std::endl;
	if (pairedVector.size() % 2 != 0){
		std::cout << "this is the number -> " << pairedVector[pairedVector.size() - 1].number << std::endl;
		pend.push_back(pairedVector[pairedVector.size() - 1]);
	}
	main = recursivelySortElements(main);
	// std::cout << "main: ";
	// printElementVector(main);
	// printElementVector(pend);
	std::cout << "yoooo " << std::endl;
	insertElements(main, pend);

	return main;
}


void PmMergeMe::performMergeInsertion(std::vector<int>& vector){
	//creates a struct that holds numbers with their pairs
	std::vector<element> pairedVector = assignNumberPairs(vector);
	pairedVector = recursivelySortElements(pairedVector);
	
}

void PmMergeMe::sortAndDisplayResults() {
	std::vector<int> tempVector = _vector;

	if (tempVector.size() % 2 != 0) {
		_oddElement = tempVector.back();
		tempVector.pop_back();
	}
	performMergeInsertion(tempVector);
	if (_oddElement != -1) {
		addOddElement(tempVector);
	}

	// std::cout << "YPPPP" << std::endl;
	// printVector (tempVector);
}

void printElementVector(std::vector<element>& vector){
	for (size_t i = 0; i < vector.size(); i++){
		std::cout << "| " << vector[i].number << " ";
	}
	std::cout << "\n";
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

// void PmMergeMe::performBinarySearch(std::vector<int>& main, std::vector<int>& pend, size_t blockSize) {
// 	if (pend.empty())
// 		return ;
// 	size_t amountBlocks = pend.size() / blockSize;
// 	std::vector<int> jacobsthalnumbers = generateJacobsthal(amountBlocks);
// 	size_t jcIndex = 3; //J[2]
// 	size_t previousJacobsthal = 1; // J[1]
// 	std::vector<int> currentBlock;
// 	size_t insertedBlocks = 0;
// 	std::vector<bool> blockIsInserted(amountBlocks, false);

// 	// std::cout << "    [Insertion Phase] Total Blocks to insert: " << amountBlocks << std::endl;

// 	while (insertedBlocks < amountBlocks) {
// 		if (jcIndex >= jacobsthalnumbers.size()){
// 			//I don't get this check
// 			// std::cout << "break" << std::endl;
// 			break;
// 		}
// 		size_t currentJacobsthal = static_cast<size_t>(jacobsthalnumbers[jcIndex]);
// 		for (size_t k = currentJacobsthal; k > previousJacobsthal; --k) {
// 			size_t blockIndex = k - 2;
// 			if (k >= 2 && blockIndex < amountBlocks && !blockIsInserted[blockIndex]) {
// 				size_t pendIndex = blockIndex * blockSize;
// 				if (pendIndex < pend.size()) {
// 					int lastElementPend = pend[pendIndex + blockSize - 1];
// 					std::vector<int> lastElementsMain;
// 					for (size_t i = 0; i + blockSize <= main.size(); i += blockSize) {
// 						lastElementsMain.push_back(main[i + blockSize - 1]);
// 					}
// 					auto lastElementsPosition = std::upper_bound(lastElementsMain.begin(), lastElementsMain.end(), lastElementPend);
// 					int lastElementIndex = std::distance(lastElementsMain.begin(), lastElementsPosition);
// 					int insertIndex = blockSize * lastElementIndex;
// 					currentBlock.clear(); //check if we need
// 					for (size_t i = 0; i < blockSize; i++) {
// 						currentBlock.push_back(pend[i + pendIndex]);
// 					}
// 					// std::cout << "        Inserting Block #" << blockIndex + 1 << " (size " << blockSize << ") at index " << insertIndex; // ADD THIS
//                     // std::cout << " (" << insertedBlocks + 1 << "/" << amountBlocks << " blocks complete)..." << std::endl; // ADD THIS
// 					main.insert(main.begin() + insertIndex, currentBlock.begin(), currentBlock.end());

// 					// std::cout << "        Insertion of Block #" << blockIndex + 1 << " COMPLETE. Vector size: " << main.size() << std::endl;

// 					blockIsInserted[blockIndex] = true;
// 					insertedBlocks++;
// 					// std::cout << "binary search main :-> ";
//                     // printVector(main);
//                     // std::cout << std::endl;
// 				}
// 				// std::cout << "hellooooo\n";
// 			}
// 			// std::cout << "helloo1\n";
// 		}
// 				previousJacobsthal = currentJacobsthal;
// 				jcIndex++;
// 	}
// }

// void PmMergeMe::recursiveInsertion(std::vector<int>& partiallySortedVector, size_t blockSize) {
// 	if (blockSize == 0)
// 		return ;
// 	// std::cout << "[Recursive Insertion] Processing Blocks of Size: " << blockSize << std::endl;
// 	std::vector<int> main;
// 	std::vector<int> pend;
// 	std::vector<int> remaining;
// 	bool isMain = true;
// 	size_t i;
// 	// std::cout << "block size is " << blockSize << std::endl;
// 	for (i = 0; i < 2 * blockSize; i++) { //a1
// 		main.push_back(partiallySortedVector[i]);
// 		// std::cout << "a1: " << partiallySortedVector[i] << std::endl;
// 	}
// 	// maybe here we should check if we can fit to add numbers into the pend before going into the next loop in the case that we can't fit a full blockSize
// 	if (i + blockSize <= partiallySortedVector.size()) {
// 		for (size_t j = 0; j < blockSize; j++) {
// 			pend.push_back(partiallySortedVector[i++]);
// 		}
// 	}
// 	while (i < partiallySortedVector.size()) {
// 		// size_t steps = 0;
// 		if (i + blockSize <= partiallySortedVector.size()) {
// 			if (isMain) {
// 				for (size_t j = 0; j < blockSize; j++) {
// 					main.push_back(partiallySortedVector[i]);
// 					i++;
// 					// steps++;
// 				}
// 			}
// 			else{
// 				for (size_t j = 0; j < blockSize; j++) {
// 					pend.push_back(partiallySortedVector[i]);
// 					i++;
// 					// steps++;
// 				}
// 			}
// 		}
// 		else {
// 			break;
// 		}
// 		isMain = !isMain;
// 		// std::cout << "PPPPPPPPi: " << i << "size: " << partiallySortedVector.size() << std::endl;

// 	}
// 	// std::cout << "main: ";
// 	// printVector(main, blockSize);
// 	// std::cout << std::endl;
// 	// std::cout << "pend: ";
// 	// printVector(pend, blockSize);
// 	// std::cout << std::endl;
// 	while (i < partiallySortedVector.size()) {
// 		remaining.push_back(partiallySortedVector[i]);
// 		i++;
// 	}
// 	// std::cout << "remaining: ";
// 	// printVector(remaining, blockSize);
// 	// std::cout << std::endl;
// 	// size_t pendBlocks = pend.size() / blockSize;
// 	// std::vector<int> insertOrder = calculateInsertOrder(blockSize, pendBlocks);
// 	// std::cout << "Insert orderrr: ";
// 	// printVector(insertOrder);
// 	// std::cout << std::endl;
// 	performBinarySearch(main, pend, blockSize);
// 	// std::cout << "[Recursive Insertion] Block Size " << blockSize << " Insertion COMPLETE. Recursing..." << std::endl;
// 	for (size_t i = 0; i < remaining.size(); i++) {
// 		main.push_back(remaining[i]);
// 	}
// 	partiallySortedVector.clear();
// 	partiallySortedVector = main;
// 	// std::cout << "End of recursion with blocksize " << blockSize << ", the main is-> ";
// 	// printVector(partiallySortedVector);
// 	// std::cout << std::endl;
// 	recursiveInsertion(partiallySortedVector, blockSize / 2);
// }


// void PmMergeMe::recursiveSort(std::vector<int>& data, size_t blockSize, int level){
// 	if (blockSize * 2 > data.size()) {
// 		// std::cout << "level-> " << level << std::endl;
// 		// std::cout << "--- Phase 1 Complete --- Starting Insertion Phase (Block Size: " << blockSize / 2 << ")" << std::endl;
// 		recursiveInsertion(data, blockSize / 2);
// 		return ;
// 	} // here we can add the insertion recursively
// 	// std::cout << "BEFORE LEVEL " << level << std::endl; 
// 	// std::cout << "[Recursive Sort] Processing Level " << level << " (Block Size: " << blockSize << ")" << std::endl;
// 	for (size_t i = 0; i + (2 *blockSize) <= data.size(); i += 2 * blockSize) {
// 		size_t block1end = i + blockSize - 1;
// 		size_t block2end = std::min(i + 2 * blockSize - 1, data.size() - 1);
// 		if (level == 1 && data[block1end] > data[block2end]) {
// 				std::swap(data[block1end], data[block2end]);
// 		}
// 		else if (data[block1end] > data[block2end]) {
// 			// std::cout << "COMPARING " << data[block1end] << " WITH " << data[block2end] << std::endl;
// 			std::rotate(data.begin() + i, data.begin() + i + blockSize, data.begin() + block2end + 1);
// 		}
		
// 	}
// 	printVector(data, blockSize);
// 	// std::cout << "AFTER LEVEL " << level << std::endl; 
// 	// printVector(data, blockSize);
// 	recursiveSort(data, 2 * blockSize, level + 1);
// }
