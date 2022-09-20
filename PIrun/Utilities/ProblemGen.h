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
	std::string GetUserInput();
	bool wasAnswerGood(char cActionDone);
	void generateSelf();
	void problemSummary();
public:
	bool DisplayProblem();
	bool IsAnsGood();
	double GiveProblemPointWeight();
	void SaveProblem(std::ofstream &filePtr);
	void showProblemDone();
	int nProblemId;
	Problem(int Difficulty, int _ID); // Initializing problem constructor
	Problem(int nProbId, double dbPoints, double dbC1, char cAD, double dbC2, double dbSolutExp, double dbSolutActual, bool bWasGood); 
	// Constructor used for loading problems
};