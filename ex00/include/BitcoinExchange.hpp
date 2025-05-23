#pragma once

#include "Date.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>

class BitcoinExchange {
	private:
		std::map<Date, float> exchangeRate;
		void loadDatabase(const std::string& databaseName);
		void parseLine(const std::string& line);
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& database);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

};