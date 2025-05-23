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
	}
}

static std::string trim(std::string& string) {
	size_t start = string.find_first_not_of(" \t\r\f");
	size_t end = string.find_last_not_of(" \t\r\f");
	std::string trimmedStr = string.substr(start, end - start + 1);
	return (trimmedStr);
}

static void processLine(const std::string& line) {
	std::istringstream	sline(line);
	std::string			dateStr;
	std::string				valueStr;
	float					value;

	std::getline(sline, dateStr, '|');
	std::getline(sline, valueStr);
	Date date(trim(dateStr));
	std::cout << "date iss ; " << dateStr << std::endl;
	std::istringstream sValue(valueStr);
	if (!(sValue >> value) || !(sValue.eof()) || value < 0 || value > 1000)
		throw std::invalid_argument("Error: Bitcoin amount is wrong " + valueStr);
}

void BitcoinExchange::processInput(const std::string& file) {
	std::ifstream input(file);
	std::string line;

	if (!input.is_open())
		throw std::runtime_error("Error: Couldn't open text file\n");
	std::getline(input, line);
	while (std::getline(input, line)) {
		if (line.empty())
			continue;
		processLine(line);
	}
}