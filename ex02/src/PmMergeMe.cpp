#include "../include/PmMergeMe.hpp"
#include "../include/PmMergeMeD.hpp"


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


void PmMergeMe::addOddElement(std::vector<int>& main) {
	auto oddElementPosition = std::lower_bound(main.begin(), main.end(), _oddElement);
	if (oddElementPosition == main.end()) {
		main.push_back(_oddElement);
	}
	else {
		int oddElementPositionIndex = std::distance(main.begin(), oddElementPosition);
		main.insert(main.begin() + oddElementPositionIndex, _oddElement);
	}
}

std::vector<int> generateJacobsthal(int n) {
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
	return pairedVector;
}

int PmMergeMe::findPair(std::vector<element>& main, element& elementToInsert){
	for (int i = 0; i < (int)main.size(); i++){
		if (elementToInsert.partner == main[i].number){
			return i;
		}
	}
	return -1;
}

void PmMergeMe::performBinarySearch(std::vector<element>& main, element& elementToInsert){
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


void PmMergeMe::insertElements(std::vector<element>& main, std::vector<element>& pend){
	//do we need to check if pend is empty?
	main.insert(main.begin(), pend[0]);
	pend.erase(pend.begin());
	size_t pendSize = pend.size();
	std::vector<bool> inserted(pendSize, false);
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

std::vector<element> PmMergeMe::recursivelySortElements(std::vector<element>& pairedVector){
	if (pairedVector.size() == 1){
		return pairedVector;
	}
	std::vector<element> main;
	std::vector<element> pend;
	for (size_t i = 0; i < pairedVector.size(); i += 2){
		if ((i + 1) > pairedVector.size() - 1){
			break; 
		}
		if (pairedVector[i].number > pairedVector[i + 1].number){
			element mainElement = pairedVector[i];
			element pendElement = pairedVector[i + 1];
			mainElement.partner = pendElement.number;
			pendElement.partner = mainElement.number;
			main.push_back(mainElement);
			pend.push_back(pendElement);
		} else {
			element mainElement = pairedVector[i + 1];
			element pendElement = pairedVector[i];
			mainElement.partner = pendElement.number;
			pendElement.partner = mainElement.number;
			main.push_back(mainElement);
			pend.push_back(pendElement);
		}
	}
	if (pairedVector.size() % 2 != 0){
		pend.push_back(pairedVector[pairedVector.size() - 1]);
	}
	main = recursivelySortElements(main);
	insertElements(main, pend);

	return main;
}


void PmMergeMe::performMergeInsertion(std::vector<int>& vector){
	//creates a struct that holds numbers with their pairs
	std::vector<element> pairedVector = assignNumberPairs(vector);
	pairedVector = recursivelySortElements(pairedVector);
	vector.clear();
	for (size_t i = 0; i < pairedVector.size(); i++){
		vector.push_back(pairedVector[i].number);
	}
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

	std::cout << "vector" << std::endl;
	printVector (_vector, "Before");
	printVector(tempVector, "After");
}

void printElementVector(std::vector<element>& vector){
	for (size_t i = 0; i < vector.size(); i++){
		std::cout << "| " << vector[i].number << " ";
	}
	std::cout << "\n";
}

static void printDuration(double durationV, double durationD, size_t size){
	std::cout << "Time to process a range of " << size << " elements with std::vector : " << \
	std::fixed << std::setprecision(5) <<  durationV << " us" << std::endl;
	std::cout << "Time to process a range of " << size << " elements with std::deque : " << \
	std::fixed << std::setprecision(5) << durationD << " us" << std::endl;
}

void runPmMerge(char* av[]) {
	try {
		checkInput(av);
		std::vector<int> unsortedVector = convertToVector(av);
		PmMergeMe object(unsortedVector);
		std::deque<int> unsortedDeque = convertToDeque(av);
		PmMergeMeD objectDeque(unsortedDeque);
		auto startTimeV = std::chrono::high_resolution_clock::now();
		object.sortAndDisplayResults();
		auto endTimeV = std::chrono::high_resolution_clock::now();
		double durationV = std::chrono::duration_cast<std::chrono::microseconds>(endTimeV - startTimeV).count();
		auto startTimeD = std::chrono::high_resolution_clock::now();
		objectDeque.sortAndDisplayResults();
		auto endTimeD = std::chrono::high_resolution_clock::now();
		double durationD = std::chrono::duration_cast<std::chrono::microseconds>(endTimeD - startTimeD).count();
		printDuration(durationV, durationD, unsortedVector.size());
	}
	catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

