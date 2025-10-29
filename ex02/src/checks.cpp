#include "../include/PmMergeMe.hpp"

void checkInput(char* av[]){
	for (int i = 1; av[i]; i++) {
		std::string currentArg = av[i];
		std::stringstream s(currentArg);
		int currentInt;
		if (!(s >> currentInt) || !s.eof())
			throw std::invalid_argument("Input is not an integer " + currentArg);
		// std::cout << "current int: " << currentInt << std::endl;
	}
}

std::vector<int> convertToVector(char* av[]) {
	std::vector<int> vector;
	std::string firstElement = av[1];
	int firstInteger = std::stoi(firstElement);
	vector.push_back(firstInteger);
	for (int i = 2; av[i]; i++) {
		std::string currentElementStr = av[i];
		int currentElementInt = std::stoi(currentElementStr);
		if (currentElementInt < 0){
			throw std::invalid_argument("Negative integer is not allowed " + currentElementStr);
		}
		if (find(vector.begin(), vector.end(), currentElementInt) != vector.end()) {
			throw std::invalid_argument("Duplicate number found " + currentElementStr);
		}
		vector.push_back(currentElementInt);
	}
	return vector;
}

void printVector(std::vector<int>& vector, std::string beforeOrAfter) {
	std::cout << beforeOrAfter << ": ";
	for (size_t i = 0; i < vector.size(); i++){
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}