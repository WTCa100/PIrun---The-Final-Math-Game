#pragma once
#include"Player.h"


int Player::getLatestId()
{
	if (isInitialLaunch)
		nID = 1;
	else
	{
		std::cout << "Implement loading latest ID here\n";
		nID = 2137;
		
	}
	return 0;
}

void Player::getInitialUserName()
{
	do
	{
		std::cout << "Enter your username:\n";
		std::getline(std::cin, this->strUsername);
		if (Validate::isEntryEmpty(this->strUsername))
			std::cout << "Nickname must be at least 1 character long!\n";

	} while (Validate::isEntryEmpty(this->strUsername));
}



void Player::SavePlayerProgress(std::ofstream &filePtr)
{
	for (auto i = ProblemSet.begin(); i != ProblemSet.end(); i++)
	{
		i->second.SaveProblem(filePtr);
	}
}

int Player::givePlayerId()
{
	return this->nID;
}

void Player::DisplayProblems()
{
	for (auto i = ProblemSet.begin(); i != ProblemSet.end(); i++)
	{
		std::cout << i->first << ": ";
		i->second.showProblemDone();
	}
}


void Player::AssignProblem(Problem currentProblem)
{
	this->ProblemSet.insert(std::make_pair(currentProblem.nProblemId, currentProblem));
}

void Player::AddPoint(int dbPointValue)
{
	this->dbPointsEarned += dbPointValue;
}

Player::Player(bool isInitial)
{
	this->ProblemSet.clear();
	this->isInitialLaunch = isInitial;
	getLatestId();
	getInitialUserName();
	std::cout << "Hello " << this->strUsername << "!\n Your id is: " << this->nID << "\n";
}