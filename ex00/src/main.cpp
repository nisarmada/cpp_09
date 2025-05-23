#include "../include/BitcoinExchange.hpp"
#include "../include/Date.hpp"

int main () {
	try {
		Date date("1999-03-03");
		std::cout << date << std::endl;
		BitcoinExchange b("data.csv");
	}
	catch (std::exception& e) {
		std::cerr << "Caught error in main: " << e.what() << std::endl;	}
}