#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

class BitcoinExchange {
	private:
		std::map<Date, float> exchangeRate;
	
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string& database);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);


};