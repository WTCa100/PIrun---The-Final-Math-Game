#pragma once
#include<iomanip>
#include<iostream>
#include<ctime>
#include<string>
#include<cmath>

#include"Menu/InputValidator/InputCheck.h"
const std::string ActionList = "+-*/";

class Problem
{
private:
	int nDiff;
	char cAct;
	double dbComp1, dbComp2;
	double dbExpected, dbActual;
	double GenerateNum(int Dif);
	char GenerateAction();
	double GenerateSolution();
	double GetUserInput();
	bool wasAnswerGood(char cActionDone);
	void generateSelf();
public:
	Problem(int Difficulty);
};