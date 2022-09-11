#include <iostream>
#include"Utilities/Menu/Menu.h"

int main()
{
	Menu* gameMenu = new Menu;
	gameMenu->mainDisplay();
	delete gameMenu;
}