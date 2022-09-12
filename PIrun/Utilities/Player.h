#pragma once
#include<string>
#include<fstream>

#include "Menu/Menu.h"
#include "Menu/Pathing/Paths.h"

class Player : protected Menu
{
private:
	int nID;
	std::string strUsername;
	int getLatestId();
public:
	Player();

};