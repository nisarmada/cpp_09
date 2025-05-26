#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <exception>
#include <sstream>

class RPN {
	private:
		std::stack<int> Stack;
		void parseExpression(const std::string& expression);
		bool isValidNumber(std::string& token);
		void additionOperation();
		void subtractionOperation();
		void multiplicationOperation();
		void divisionOperation();
	public:
		RPN();
		RPN(const std::string& expression);
		~RPN();

		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
};