#include "ProblemGen.h"
// Generate a number depending on Difficulty
double Problem::GenerateNum(int Dif)
{
	switch (Dif)
	{
	default:
		std::cout << "Unknown error has occured\n";
		break;
	case 1:
		return rand() % static_cast<long>(pow(10, Dif)) + 1;
		break;		
	case 2:
		return rand() % static_cast<long>(pow(10, Dif)) + 1;
		break;
	case 3:
		return rand() % static_cast<long>(pow(10, Dif)) + 1;
		break;
	case 4:
		return rand() % static_cast<long>(pow(10, Dif)) + 1;
		break;
	case 5:
		return rand() % static_cast<long>(pow(10, Dif)) + 1;
		break;
	case 6:
		return rand() % static_cast<long>(pow(10, Dif)) + 1;
		break;
	}
}
// Generate only action char
char Problem::GenerateAction()
{
	return ActionList[rand()%ActionList.size()];
}

double Problem::GenerateSolution()
{
	switch (this->cAct)
	{
	default:
		std::cout << "An error occured\n";
		break;
	case '+':
		return this->dbComp1 + this->dbComp2;
		break;
	case '-':
		return this->dbComp1 - this->dbComp2;
		break;
	case '*':
		return this->dbComp1 * this->dbComp2;
		break;
	case '/':
		return this->dbComp1 / this->dbComp2;
		break;
	}
}

double Problem::GetUserInput()
{
	std::string strTmpValueHolder;
	do
	{
		std::cout << "Answer: ";
		std::getline(std::cin, strTmpValueHolder);
		if (!Validate::isInputNumber(strTmpValueHolder))
		{
			std::cout << "Plase enter a numeric value!\n";
		}
	} while (!Validate::isInputNumber(strTmpValueHolder));
	return std::stod(strTmpValueHolder);
}
// There really is no better way (to my knowladge) on checking if a floating point (especially high precision double) is equal to another
// The expression presented here comes from Bruce Dawnson and his lovely blog https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
bool Problem::wasAnswerGood(char cActionDone)
{
	std::string tmpExpect = std::to_string(this->dbExpected);
	std::string tmpActual = std::to_string(this->dbActual);
	switch (cActionDone)
	{
	default:
		return fabs(dbExpected - dbActual) < DBL_EPSILON;
	case '/':
		return tmpExpect.find(tmpActual) != std::string::npos;
	}
	return false; // If none are presented return false val;
}

void Problem::generateSelf()
{
	dbComp1 = GenerateNum(this->nDiff);
	dbComp2 = GenerateNum(this->nDiff);
	cAct = GenerateAction();
	dbExpected = GenerateSolution();

}

void Problem::problemSummary()
{
	std::cout << "Expecter problem answer was: " << dbExpected << std::endl;
	std::cout << "You answered: " << dbActual;
	if(bIsAnsGood)
	{
		std::cout << ". Which was correct!\n"; // Later add info about points
		return;
	}
	std::cout << ". Which was not correct!\n";  
}

Problem::Problem(int Difficulty, int _ID)
{
	this->nDiff = Difficulty;
	this->nProblemId = _ID;
	generateSelf();
	std::cout << _ID << ": Your problem is \n";
	if (this->cAct != '/')
		std::cout << std::setprecision(2) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << dbExpected << std::endl;
	else
		std::cout << std::setprecision(6) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << dbExpected << std::endl;
	dbActual = GetUserInput();
	bIsAnsGood = wasAnswerGood(this->cAct);
	problemSummary();
}
