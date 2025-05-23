#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& database) {
	loadDatabase(database);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseLine(const std::string& line) { //We definitely need to check for edge cases
	if (line.empty())
		return ;
	std::istringstream iss(line);
	std::string dateStr;
	std::string valueStr;

	std::getline(iss, dateStr, ',');
	std::getline(iss, valueStr);
	// std::cout << "line  is : " << dateStr << "-" << valueStr << std::endl;
	Date date(dateStr);
	std::istringstream valueCheck(valueStr);
	float value;
	if (!(valueCheck >> value) || !(valueCheck.eof())) {
		throw std::invalid_argument("Error: non numeric character in exchange rate: " + valueStr);
	}
	if (value < 0)
		throw std::invalid_argument("Error: value is negative: " + valueStr);
	this->exchangeRate[date] = value;
}

void BitcoinExchange::loadDatabase(const std::string& database) {
	std::ifstream file(database);
	std::string line;
	
	if (!file.is_open())
		throw std::runtime_error("Error: Couldn't open the file\n");
	std::getline(file, line);
	std::cout << line << std::endl;
	while (std::getline(file, line)) {
		try {
			parseLine(line);

		}
		catch (const std::exception& e) {
			std::cerr << "Skipping invalid line: " << e.what() << std::endl;
			continue;
		}
		// std::cout << line << std::endl;
	}
}