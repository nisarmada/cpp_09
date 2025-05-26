#include "../include/BitcoinExchange.hpp"
#include "../include/Date.hpp"

int main (int ac, char* av[]) {
	if (ac != 2)
	{
		std::cerr << "Wrong amount of arguments. Please follow the format ./btc [filename]" << std::endl;
		return 1;
	}
		BitcoinExchange btc("data.csv");
		btc.processInput(av[1]);
		// btc.searchDate()
}