#include "../include/PmergeMe.hpp"

int main (int ac, char* av[]) {
	if (ac <= 2) {
		std::cerr << "Error: Not enough integers to sort" << std::endl;
		return 1;
	}
	runPmMerge(av);

	return 0;
}