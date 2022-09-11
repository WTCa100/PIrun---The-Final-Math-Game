#pragma once
#include"Menu.h"


struct stat info;

void Menu::makeDir(int fType)
{
	std::string _exBatFile = MAKE_FILES;
	switch (fType)
	{
	case 1: // Highscores
		_exBatFile += "MAKE_HIGHSCORES.bat";
		InitialBootUp = true;
		break;
	case 2: // Detail records
		_exBatFile += "MAKE_DETAILED_RECORDS.bat";
		break;
	case 3: // Problem sets
		_exBatFile += "MAKE_PROBLEM_SET.bat";
		break;
	}
	std::cout << "Creating file...\n";
	std::cout << "Executing " << _exBatFile << std::endl;
	_exBatFile += " >nul";
	system(_exBatFile.c_str());
}

void Menu::checkEssentialDirectories()
{
	checkDir(HIGHSCORES);
	checkDir(DETAILED_RECORDS);
	checkDir(PROBLEM_SET);
}

void Menu::checkDir(std::string _FILENAME)
{
	bool bDoesDirExists = false;
	do
	{
		if (lookForDir(_FILENAME))
			bDoesDirExists = true;
		else
		{
			if (_FILENAME == HIGHSCORES)
				makeDir(1);
			else if (_FILENAME == DETAILED_RECORDS)
				makeDir(2);
			else if (_FILENAME == PROBLEM_SET)
				makeDir	(3);
			else { std::cout << "Unknown error orccured.\n"; system("exit"); }
		}
	} while (!bDoesDirExists);
}

bool Menu::lookForDir(std::string _DIRpath)
{
	if (stat(_DIRpath.c_str(), &info) != 0)
	{
		std::cout << "Cannot access " << _DIRpath << "\n";
		return false;
	}
	std::cout << _DIRpath << " found!\n";
	std::string Command = "cd " + _DIRpath;
	return true;
}

void Menu::mainDisplay()
{
	std::cout << "Welcome to PIrun - the final math game!\n";
	std::cout << "Options:\n";
}

Menu::Menu()
{
	InitialBootUp = false;
	checkEssentialDirectories();
}