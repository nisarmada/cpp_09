#pragma once

#include "BitcoinExchange.hpp"


class Date {
	private:
		int _year;
		int _month;
		int _day;
		bool isValid() const;
		bool isLeapYear() const;
	public:
		Date();
		Date(const std::string& date);
		~Date();
		Date(const Date& other);
		Date& operator=(const Date& other);

		int getYear() const;
		int getMonth() const;
		int getDay() const;

		bool operator<(const Date& other) const;
		bool operator==(const Date& other) const;
};

std::ostream& operator<<(std::ostream&, const Date& other);