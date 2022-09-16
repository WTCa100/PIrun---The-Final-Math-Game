#pragma once
#include<iomanip>
#include<iostream>
#include<ctime>
#include<string>
#include<cmath>
#include<fstream>

#include"Menu/InputValidator/InputCheck.h"
const std::string ActionList = "+-*/";

class Problem
{
private:
	bool bIsAnsGood;
	int nDiff;
	char cAct;
	double dbPointWeight;
	double dbComp1, dbComp2;
	double dbExpected, dbActual;
	double GeneratePointWeight(char Act, int Dif);
	double GenerateNum(int Dif);
	char GenerateAction();
	double GenerateSolution();
	double GetUserInput();
	bool wasAnswerGood(char cActionDone);
	void generateSelf();
	void problemSummary();
protected:
public:
	void SaveProblem(std::ofstream &filePtr);
	void showProblemDone();
	int nProblemId;
	Problem(int Difficulty, int _ID);
};