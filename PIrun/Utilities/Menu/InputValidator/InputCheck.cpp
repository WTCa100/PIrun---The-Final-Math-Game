#include "InputCheck.h"
#pragma once

bool Validate::isWithtinRange(int nSample, int nMaxVal, int nMinVal)
{
	if (nSample > nMaxVal || nSample < nMinVal)
		return false;
	return true;
}

bool Validate::isInputNumber(std::string strSample)
{
	if (strSample.empty())
		return false;
	bool bIsNegative = false;
	if (strSample[0] == '-')
		bIsNegative = true;
	for (int i = 0; i < strSample.size(); i++)
	{
		if (bIsNegative && i == 0)
			continue;
		if (bIsNegative && (strSample[i] == '-' && i != 0)) // Check if there is additional '-' char in string
			return false;
		if (!isdigit(strSample[i]))
			return false;
	}

	return true;
}

Validate::Validate(std::string strInput)
{
	this->strCheck = strInput;
}
