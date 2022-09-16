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

void Player::AddPoint(int dbPointValue)
{
	this->dbPointsEarned + dbPointValue;
}

Player::Player(bool isInitial)
{
	this->isInitialLaunch = isInitial;
	getLatestId();
	getInitialUserName();
	std::cout << "Hello " << this->strUsername << "!\n Your id is: " << this->nID << "\n";
}