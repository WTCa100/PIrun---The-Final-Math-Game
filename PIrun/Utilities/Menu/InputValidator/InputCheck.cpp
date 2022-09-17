#include "InputCheck.h"
#pragma once

bool Validate::isYesNoValid(std::string strSample)
{
	return std::toupper(strSample[0]) == 'Y' || std::toupper(strSample[0] == 'N');
}

bool Validate::isEntryEmpty(std::string strSample)
{
	return strSample.empty();
}

bool Validate::isWithtinRange(int nSample, int nMaxVal, int nMinVal)
{
	if (nSample > nMaxVal || nSample < nMinVal)
		return false;
	return true;
}

bool Validate::isInputNumber(std::string strSample)
{
	if (Validate::isEntryEmpty(strSample))
		return false;
	bool bIsNegative = false;
	bool bHasComma = false; // Comma and dot are treadet indifferently
	size_t commaPos = strSample.find(','); // Try to locate comma separation
	if (commaPos == std::string::npos)
	{
		commaPos = strSample.find('.');
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
		if (bIsNegative && i == 0)
			continue;
		if (bIsNegative && (strSample[i] == '-' && i != 0)) // Check if there is additional '-' char in string
			return false;
		if (bHasComma && i == commaPos)
			continue;
		if (!isdigit(strSample[i]))
			return false;
	}

	return true;
}

std::string Validate::MakeUpper(std::string& strSample)
{
	for (int i = 0; i != strSample.size(); i++)
	{
		strSample[i] = std::toupper(strSample[i]);
	}
	return strSample;
}



Validate::Validate(std::string strInput)
{
	this->strCheck = strInput;
}
