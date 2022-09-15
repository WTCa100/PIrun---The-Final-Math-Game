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

bool Problem::wasAnswerGood(char cActionDone)
{
	switch (cActionDone)
	{
	default: // TODO fill up
		break;
	}
	return false;
}

void Problem::generateSelf()
{
	dbComp1 = GenerateNum(this->nDiff);
	dbComp2 = GenerateNum(this->nDiff);
	cAct = GenerateAction();
	dbExpected = GenerateSolution();

}

Problem::Problem(int Difficulty)
{
	this->nDiff = Difficulty;
	generateSelf();
	std::cout << "Your problem is \n";
	std::cout << std::setprecision(2) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << dbExpected << std::endl;
	GetUserInput();
}
