#include "CalculatorLogic.h"
#include <wx/string.h>
#include <iostream>
#include <sstream>

wxString CalculatorLogic::calculateExpression(wxString& expression) {

	// convert wxString to std String
	std::string stdExpression = expression.ToStdString();
	
	// variables to store operator, numbers and result
	double num1 = 0, num2 = 0;
	char op = '\0';
	double result = 0;

	// create a string stream
	std::stringstream ss(stdExpression);

	// read num1 as a string to capture the decimals
	std::string num1Str;
	ss >> num1Str;

	// convert num1Str to a double
	std::istringstream(num1Str) >> num1;
	
	// read the operator
	ss >> op;

	// read num2 as a string to capture the decimal
	std::string num2Str;
	ss >> num2Str;

	// convert num2Str to a double
	std::istringstream(num2Str) >> num2;

	// check if the extraction of op failed (invalid format)
	if (ss.fail()) {
		return wxString("ERROR: Invalid expression format");
	}

	// perform calculations
	switch (op) {
	case '+' :
		result = num1 + num2;
		break;
	case '-' :
		result = num1 - num2;
		break;
	case '×' :
		result = num1 * num2;
		break;
	case '÷' :
		if (num2 != 0) {
			result = num1 / num2;
		}
		else {
			return wxString("ERROR: Division by zero");
		}
		break;

	default:
		return wxString("ERROR: Invalid operator");
	}

	// convert the result to a string
	std::ostringstream resultStream;
	resultStream << result;

	// convert the result back to a wxString
	wxString wxStrResult(resultStream.str());

	return wxStrResult;
};