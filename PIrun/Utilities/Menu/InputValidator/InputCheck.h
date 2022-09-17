#pragma once
#include<iostream>
#include<string>

class Validate
{
private:
	std::string strCheck;
public:
	static bool isYesNoValid(std::string strSample);
	static bool isEntryEmpty(std::string strSample);
	static bool isWithtinRange(int nSample, int nMaxVal, int nMinVal = 1);
	static bool isInputNumber(std::string strSample);
	static std::string MakeUpper(std::string& strSample);
	Validate(std::string strInput);
};