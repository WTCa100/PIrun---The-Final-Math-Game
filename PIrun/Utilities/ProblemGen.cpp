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
	return ActionList[rand()%ActionList.size() - 1];
}

Problem::Problem(int Difficulty)
{
	this->nDiff = Difficulty;
	std::cout << "Game diff selected: " << nDiff << "\n";
	dbComp1 = GenerateNum(nDiff); dbComp2 = GenerateNum(nDiff);
	std::cout << std::setprecision(2) << std::fixed << "Your comp1 is: " << dbComp1 << " Your comp2 is: " << dbComp2 << "\n";
	cAct = GenerateAction();
	std::cout << "Your action is: " << cAct <<"\n";
}
