#include "ProblemGen.h"
// Generate a number depending on Difficulty
double Problem::GenerateNum(int Dif)
{
	return rand() % static_cast<long>(pow(10, Dif)) + 1;
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
	return 0.0f;
}

std::string Problem::GetUserInput()
{
	std::string strTmpValueHolder;
	do
	{
		std::cout << "Answer: ";
		std::getline(std::cin, strTmpValueHolder);
		if (!(Validate::isInputNumber(strTmpValueHolder) || Validate::MakeUpper(strTmpValueHolder) == "CANCEL"))
		{
			std::cout << "Plase enter a numeric value!\n";
		}
	} while (!((Validate::isInputNumber(strTmpValueHolder) || Validate::MakeUpper(strTmpValueHolder) == "CANCEL")));
	return strTmpValueHolder;
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

double Problem::GeneratePointWeight(char Act, int Dif)
{
	return (pow(Dif * 0.8, 2) + pow(Act * 0.2, 2)); // Might change the formula later
}

bool Problem::isNumPrime(int nNum)
{
	if (nNum == 0 || nNum == 1 || nNum == 2) return true;
	else if (nNum % 2 == 0 && nNum > 2) return false;
	else
	{
		for (long i = 3; i <= static_cast<long>(std::sqrt(nNum)); i++)
		{
			if (nNum % i == 0)
				return false;
		}
	}
	return true;
}

void Problem::GenerateComponents(int Dif)
{
	if (Dif <= 2)
	{
		switch (this->cAct)
		{
		default:
			this->dbComp1 = GenerateNum(this->nDiff);
			this->dbComp2 = GenerateNum(this->nDiff);
			break;
		case '/':
			do
			{
				this->dbComp1 = GenerateNum(this->nDiff + 1);
			} while (isNumPrime(static_cast<long>(dbComp1)));
			do
			{
				this->dbComp2 = GenerateNum(this->nDiff);
			} while (static_cast<long>(this->dbComp1) % static_cast<long>(this->dbComp2) != 0 || this->dbComp2 == 1);
		}
	}
	else if (Dif == 3)
	{
		std::cout << "Do stuff\n";
	}
	else
	{
		std::cout << "Do even more stuff\n";
	}
}

void Problem::generateSelf()
{
	cAct = GenerateAction();
	cAct = '/';
	dbComp1 = GenerateNum(this->nDiff);
	dbComp2 = GenerateNum(this->nDiff);
	GenerateComponents(this->nDiff);
	dbPointWeight = GeneratePointWeight(this->cAct, this->nDiff);
	dbExpected = GenerateSolution();

}

void Problem::problemSummary()
{
	std::cout << "Expected problem answer was: " << dbExpected << std::endl;
	std::cout << "Player answered: " << dbActual;
	if(bIsAnsGood)
	{
		std::cout << ". Which was correct!\n"; // Later add info about points
		return;
	}
	std::cout << ". Which was not correct!\n";  
}




bool Problem::DisplayProblem()
{
	std::cout << this->nProblemId << ": This problem has " << dbPointWeight << " points:\n";
	if (this->cAct != '/')
		std::cout << std::setprecision(2) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << std::endl;
	else
		std::cout << std::setprecision(2) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << std::endl;
	std::string tmpAnsHolder = GetUserInput();
	if (tmpAnsHolder == "CANCEL")
	{
		return false;
	}
	this->dbActual = std::stod(tmpAnsHolder);
	bIsAnsGood = wasAnswerGood(this->cAct);
	problemSummary();
	return true;
}

bool Problem::IsAnsGood()
{
	return this->bIsAnsGood;
}
double Problem::GiveProblemPointWeight()
{
	return this->dbPointWeight;
}

void Problem::SaveProblem(std::ofstream& filePtr)
{
	filePtr << nProblemId << std::endl;
	filePtr << dbPointWeight << std::endl;
	filePtr << dbComp1 << std::endl;
	filePtr << cAct << std::endl;
	filePtr << dbComp2 << std::endl;
	filePtr << dbExpected << std::endl;
	filePtr << dbActual << std::endl;
	filePtr << bIsAnsGood << std::endl;
}

void Problem::showProblemDone()
{
	std::cout << "This problem had " << dbPointWeight << " points:\n";
	if (this->cAct != '/')
		std::cout << std::setprecision(2) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << dbExpected << std::endl;
	else
		std::cout << std::setprecision(6) << std::fixed << dbComp1 << " " << cAct << " " << dbComp2 << " = " << dbExpected << std::endl;
	problemSummary();
}

Problem::Problem(int Difficulty, int _ID)
{
	this->nDiff = Difficulty;
	this->nProblemId = _ID;
	generateSelf();
}

Problem::Problem(int nProbId, double dbPoints, double dbC1, char cAD, double dbC2, double dbSolutExp, double dbSolutActual, bool bWasGood)
{
	this->nDiff = 0; // Do not leave uninitialized variables
	this->nProblemId = nProbId;
	this->dbPointWeight = dbPoints;
	this->dbComp1 = dbC1;
	this->cAct = cAD;
	this->dbComp2 = dbC2;
	this->dbExpected = dbSolutExp;
	this->dbActual = dbSolutActual;
	this->bIsAnsGood = bWasGood;
}
