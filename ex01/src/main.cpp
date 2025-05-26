#include "../include/RPN.hpp"

int main (int ac, char* av[]) {
	if (ac != 2) {
		std::cerr << "Error: wrong format, please provide a string with the arithmetic expression" << std::endl;
		return 1;
	}
	try {
		RPN calculation(av[1]);
		// calculation.parseExpression(av[1]);
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
	// RPN test(av[1]);

}