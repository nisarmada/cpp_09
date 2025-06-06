#include "../include/PmergeMe.hpp"

int main (int ac, char* av[]) {
	if (ac <= 2) {
		std::cerr << "Error: Not enough integers to sort" << std::endl;
		return 1;
	}
	runPmMerge(av);

	return 0;
}

//./PmMergeMe 2 11 0 17 8 16 6 15 3 10 1 21 9 18 14 19 5 12 4 20 7 13