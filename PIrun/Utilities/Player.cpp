#pragma once
#include"Player.h"


int Player::getLatestId()
{
	if (Menu::InitialBootUp)
		nID = 1;
	else
	{
		std::cout << "Es\n";
		
	}
	return 0;
}

Player::Player()
{
}
