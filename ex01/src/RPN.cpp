#include "../include/RPN.hpp"

RPN::RPN() {}

RPN::RPN(const std::string& expression) {
	parseExpression(expression);
}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : Stack(other.Stack) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		Stack = other.Stack;
	}
	return (*this);
}

static bool isOperator(std::string& token) {
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool RPN::isValidNumber(std::string& token) {
	if (token.length() > 1 || token.empty())
		return false;
	return (std::isdigit(token[0]));
}

void RPN::additionOperation() {
	int numberB = this->Stack.top();
	this->Stack.pop();
	int numberA = this->Stack.top();
	this->Stack.pop();

	int result = numberB + numberA;
	this->Stack.push(result);
}

void RPN::subtractionOperation() {
	int numberB = this->Stack.top();
	this->Stack.pop();
	int numberA = this->Stack.top();
	this->Stack.pop();

	int result = numberA - numberB;
	this->Stack.push(result);
}

void RPN::multiplicationOperation() {
	int numberB = this->Stack.top();
	this->Stack.pop();
	int numberA = this->Stack.top();
	this->Stack.pop();

	int result = numberB * numberA;
	this->Stack.push(result);
}

void RPN::divisionOperation() {
	int numberB = this->Stack.top();
	this->Stack.pop();
	int numberA = this->Stack.top();
	this->Stack.pop();

	if (numberB == 0)
		throw std::runtime_error("Division by 0 is not allowed");
	int result = numberA / numberB;
	this->Stack.push(result);
}

void RPN::parseExpression(const std::string& expression) {
	std::stringstream	ss(expression);
	std::string			token;

	while (ss >> token) {
		if (isOperator(token)) {
			if (this->Stack.size() < 2) {
				throw std::invalid_argument("Error: not enough numbers to perform arithmetic expression");
			}
			if (token == "+") {
				additionOperation();
				// std::cout << "addition result is: " << Stack.top() << std::endl;
			}
			else if (token == "-") {
				subtractionOperation();
			}
			else if (token == "*") {
				multiplicationOperation();
			}
			else {
				divisionOperation();
			}
		}
		else {
				if (!isValidNumber(token))
					throw std::invalid_argument("Error input is invalid " + token);
				int number = std::stoi(token);
				this->Stack.push(number);
			}
	}
	if (this->Stack.size() > 1)
		throw std::runtime_error("Invalid number of arguments in the stack");
	std::cout << this->Stack.top() << std::endl;
}
