#pragma once
#include<string>
#include<fstream>

#include "Menu/Menu.h"

class Player : private Menu
{
private:
	int nID;
	std::string strUsername;
	int getLatestId();
public:
	Player();

};