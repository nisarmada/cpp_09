#include "../include/PmMergeMeD.hpp"

PmMergeMeD::PmMergeMeD() {}

PmMergeMeD::PmMergeMeD(const std::deque<int>& sequence) : _deque(sequence) {}

PmMergeMeD::~PmMergeMeD() {}

PmMergeMeD::PmMergeMeD(const PmMergeMeD& other) : _deque(other._deque) {}

PmMergeMeD& PmMergeMeD::operator=(const PmMergeMeD& other) {
	if (this != &other) {
		_deque = other._deque;
	}
	return (*this);
}

std::deque<int> convertToDeque(char* av[]) {
	std::deque<int> deque;
	std::string firstElement = av[1];
	int firstInteger = std::stoi(firstElement);
	deque.push_back(firstInteger);
	for (int i = 2; av[i]; i++) {
		std::string currentElementStr = av[i];
		int currentElementInt = std::stoi(currentElementStr);
		if (currentElementInt < 0){
			throw std::invalid_argument("Negative integer is not allowed " + currentElementStr);
		}
		if (find(deque.begin(), deque.end(), currentElementInt) != deque.end()) {
			throw std::invalid_argument("Duplicate number found " + currentElementStr);
		}
		deque.push_back(currentElementInt);
	}
	return deque;
}

void PmMergeMeD::addOddElement(std::deque<int>& main) {
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

std::deque<element> PmMergeMeD::assignNumberPairs(std::deque<int>& deque){
	std::deque<element> pairedDeque;
	for (size_t i = 0; i < deque.size(); i++){
		element currentNumber;
		currentNumber.number = deque[i];
		currentNumber.originalIndex = i;
		if (i % 2 == 0){
			currentNumber.partner = deque[i + 1];
		}
		else{
			currentNumber.partner = deque[i - 1];
		}
		pairedDeque.push_back(currentNumber);
	}
	return pairedDeque;
}

int PmMergeMeD::findPair(std::deque<element>& main, element& elementToInsert){
	for (int i = 0; i < (int)main.size(); i++){
		if (elementToInsert.partner == main[i].number){
			return i;
		}
	}
	return -1;
}

void PmMergeMeD::performBinarySearch(std::deque<element>& main, element& elementToInsert){
	int low = 0;
	int high = findPair(main, elementToInsert);

	if (high < 0){
		return ;
	}
	while (low <= high){
		int middle = low + (high - low) / 2;
		if (main[middle].number >= elementToInsert.number){
			high = middle - 1;
		}
		else if (main[middle].number < elementToInsert.number){
			low = middle + 1;
		}
	}
	main.insert(main.begin() + low, elementToInsert);
}

void PmMergeMeD::insertElements(std::deque<element>& main, std::deque<element>& pend){
	//do we need to check if pend is empty?
	main.insert(main.begin(), pend[0]);
	pend.erase(pend.begin());
	size_t pendSize = pend.size();
	std::deque<bool> inserted(pendSize, false);
	std::vector<int> jacobsthalNumbers = generateJacobsthal(pendSize);
	size_t previousJacobsthal = 1;
	size_t jacobIndex = 1;	
	while(jacobIndex < jacobsthalNumbers.size()){
		size_t currentJacobsthal = std::min((size_t)jacobsthalNumbers[jacobIndex], pendSize);

		//insert elements from current Jacobsthal down to previous J + 1
		for (int i = currentJacobsthal - 1; i >= (int)previousJacobsthal; --i){
			if (i < (int)pendSize && !inserted[i]){
				performBinarySearch(main, pend[i]);
				inserted[i] = true;
			}
		}
		previousJacobsthal = currentJacobsthal;
		jacobIndex++;

		//if we covered everything, stop
		if (previousJacobsthal >= pendSize)
			break;
	}
	for (size_t i = 0; i <pendSize; i++){
		if (!inserted[i]){
			performBinarySearch(main, pend[i]);
		}
	}
}

std::deque<element> PmMergeMeD::recursivelySortElements(std::deque<element>& pairedDeque){
	if (pairedDeque.size() == 1){
		return pairedDeque;
	}
	std::deque<element> main;
	std::deque<element> pend;
	for (size_t i = 0; i < pairedDeque.size(); i += 2){
		if ((i + 1) > pairedDeque.size() - 1){
			break; 
		}
		if (pairedDeque[i].number > pairedDeque[i + 1].number){
			element mainElement = pairedDeque[i];
			element pendElement = pairedDeque[i + 1];
			mainElement.partner = pendElement.number;
			pendElement.partner = mainElement.number;
			main.push_back(mainElement);
			pend.push_back(pendElement);
		} else {
			element mainElement = pairedDeque[i + 1];
			element pendElement = pairedDeque[i];
			mainElement.partner = pendElement.number;
			pendElement.partner = mainElement.number;
			main.push_back(mainElement);
			pend.push_back(pendElement);
		}
	}
	if (pairedDeque.size() % 2 != 0){
		pend.push_back(pairedDeque[pairedDeque.size() - 1]);
	}
	main = recursivelySortElements(main);
	// std::cout << "main: ";
	// printElementVector(main);
	// printElementVector(pend);
	insertElements(main, pend);

	return main;
}

void PmMergeMeD::performMergeInsertion(std::deque<int>& deque){
	//creates a struct that holds numbers with their pairs
	std::deque<element> pairedDeque = assignNumberPairs(deque);
	pairedDeque = recursivelySortElements(pairedDeque);
	deque.clear();
	for (size_t i = 0; i < pairedDeque.size(); i++){
		deque.push_back(pairedDeque[i].number);
	}
}

void PmMergeMeD::sortAndDisplayResults() {
	std::deque<int> tempDeque = _deque;

	if (tempDeque.size() % 2 != 0) {
		_oddElement = tempDeque.back();
		tempDeque.pop_back();
	}
	performMergeInsertion(tempDeque);
	if (_oddElement != -1) {
		addOddElement(tempDeque);
	}

	// std::cout << "YPPPP" << std::endl;
	// printDeque(tempDeque);
}


void printDeque(std::vector<int>& deque, size_t blockSize) {
	std::cout << "{";
	for (unsigned int i = 0; i < deque.size(); i++) {
		
		if (blockSize > 0 && i > 0 && i % blockSize == 0) {
			std::cout << "| ";
		}
		std::cout << deque[i];
		if (i == deque.size() - 1)
			break;
		std::cout << ", ";
	}
	std::cout << "}" << std::endl;
}

void printElementDeque(std::deque<element>& deque){
	for (size_t i = 0; i < deque.size(); i++){
		std::cout << "| " << deque[i].number << " ";
	}
	std::cout << "\n";
}