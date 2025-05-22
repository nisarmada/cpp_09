#include "../include/Date.hpp"

Date::Date() : _year(2009), _month(1), _day(2) {}

Date::Date(const std::string& date) { //maybe we need to move all the validation logic into a seperate funciton and only call the constructor in case it is correct
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		throw (std::invalid_argument("Argument format expected: YYYY-MM-DD\n"));
	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);
	if (!std::all_of(yearStr.begin(), yearStr.end(), ::isdigit) || !std::all_of(monthStr.begin(), monthStr.end(), ::isdigit) \
		|| !std::all_of(dayStr.begin(), dayStr.end(), ::isdigit))
		throw (std::invalid_argument("Error: date must contain only numeric components\n"));
	_year = std::stoi(yearStr);
	_month = std::stoi(monthStr);
	_day = std::stoi(dayStr);
	
	if (!isValid())
		throw (std::invalid_argument("Error: Date is not valid\n")); 
}

Date::~Date() {}

Date::Date(const Date& other) : _year(other._year), _month(other._month), _day(other._day) {}

Date& Date::operator=(const Date& other) {
	if (this != &other) {
		_year = other._year;
		_month = other._month;
		_day = other._day;
	}
	return (*this);
}

bool Date::operator<(const Date& other) const {
	if (_year != other._year)
		return (_year < other._year);
	if (_month != other._month)
		return (_month < other._month);
	return (_day < other._day);
}

bool Date::operator==(const Date& other) const {
	if (_year != other._year || _month != other._month || _day != other._day)
		return (false);
	return (true);
}

int Date::getYear() const {
	return _year;
}

int Date::getMonth() const {
	return _month;
}

int Date::getDay() const {
	return _day;
}

bool Date::isLeapYear() const {
	if ((_year % 4 == 0 && _year % 100 != 0) || _year % 400 == 0)
		return true;
	return false;
}

bool Date::isValid() const {
	if (_year < 0)
		return false;
	if (_month <= 0 || _month > 12)
		return false;
	if (_day <= 0 || _day > 31)
		return false;

	static const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDays = daysInMonth[_month];

	if (_month == 2 && isLeapYear())
		maxDays = 29;
	if (_day < 1 || _day > maxDays)
		return false;
	return true;
}