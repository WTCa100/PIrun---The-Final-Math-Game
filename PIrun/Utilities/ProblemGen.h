#pragma once
#include<iomanip>
#include<iostream>
#include<ctime>
#include<string>
#include<cmath>

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
	void generateSelf();
public:
	Problem(int Difficulty);
};