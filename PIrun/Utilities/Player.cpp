#pragma once
#include"Player.h"


int Player::getLatestId()
{
	if (GameState::InitialBootUp)
		nID = 1;
	else
	{
		std::cout << "Es\n";
		
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

Player::Player()
{
	getInitialUserName();
}
