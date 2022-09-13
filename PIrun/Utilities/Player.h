#pragma once
#include<string>
#include<fstream>
#include <iostream>

#include "Menu/GameState/Gamestate.h"
#include "Menu/InputValidator/InputCheck.h"
#include "Menu/Pathing/Paths.h"

class Player
{
private:
	int nID;
	std::string strUsername;
	int getLatestId(); // Obtain the ID value to give to the latest player
	void getInitialUserName(); // Constructor - get player nickname info
public:
	Player();

};