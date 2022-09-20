#include "InputCheck.h"
#pragma once

// Check if user input for Yes/No question is correct
bool Validate::isYesNoValid(std::string strSample)
{
	return std::toupper(strSample[0]) == 'Y' || std::toupper(strSample[0]) == 'N';
}
// Checks if user input is empty (as simple as that) - it's done mostly for cosmetical usage - you can aswel run "std::string.empty()" for the same results
bool Validate::isEntryEmpty(std::string strSample)
{
	return strSample.empty();
}
// Checks if provided arguments are within range
bool Validate::isWithtinRange(int nSample, int nMaxVal, int nMinVal)
{
	if (nSample > nMaxVal || nSample < nMinVal)
		return false;
	return true;
}
// Checks if a string sample is a number or not
bool Validate::isInputNumber(std::string& strSample)
{
	if (Validate::isEntryEmpty(strSample))
		return false;
	bool bIsNegative = false; // Include negative numbers
	bool bHasComma = false; // Comma and dot are treated indifferently
	size_t commaPos = strSample.find(','); // Try to locate comma separation
	if (commaPos == std::string::npos)
	{
		commaPos = strSample.find('.'); // Try to locate dot separation
		if (commaPos != std::string::npos)
			bHasComma = true;
		}
	else
	{
		bHasComma = true;
	}
	if (strSample[0] == '-')
		bIsNegative = true;
	for (int i = 0; i < strSample.size(); i++)
	{
		if (bIsNegative && i == 0) // No point of checking first char if it's negtaive value
			continue;
		if (bHasComma && i == commaPos) // No point of checking the dot character position
			continue;
		if (!isdigit(strSample[i]))
			return false;
	}
	Validate::swapCommaToDot(strSample); // Convert ',' to '.' in order to properly check user input in ProblemGen 
	return true;
}
// Swaps first left comma to dot
void Validate::swapCommaToDot(std::string& strToModify)
{
	size_t commaPos = strToModify.find(','); 
	if (commaPos == std::string::npos)
		return;
	strToModify[commaPos] = '.';
	return;
}
// Change string to be uppercased if possible
std::string Validate::MakeUpper(std::string& strSample)
{
	for (int i = 0; i != strSample.size(); i++)
	{
		strSample[i] = std::toupper(strSample[i]);
	}
	return strSample;
}

// Basic class initalization
Validate::Validate(std::string strInput)
{
	this->strCheck = strInput;
}
