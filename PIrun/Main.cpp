#include <iostream>
#include <ctime>
#include"Utilities/Menu/Menu.h"

int main()
{
	srand((unsigned)time(NULL));
	Menu* gameMenu = new Menu;
	gameMenu->mainDisplay();
	delete gameMenu;
}