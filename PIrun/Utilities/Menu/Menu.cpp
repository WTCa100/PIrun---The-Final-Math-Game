#pragma once
#include"Menu.h"

void Menu::mainDisplay()
{
	std::cout << "\nWelcome to PIrun - the final math game!\n";
	std::cout << "Options:\n";
}

Menu::Menu()
{
	InitialBootUp = false;
	checkEssentialDirectories();
	if (InitialBootUp)
		makeInitialFiles();
	else
	{
		checkEssentialFiles();
	}
	
}
/*The following methods are uset do validate wether or not essential files exists*/
void Menu::checkEssentialFiles()
{
	bool bIsInitialFileGood;
	do 
	{
		if (!lookForFile(HIGHSCORES, "Highscores.txt"))
		{
			bIsInitialFileGood = false;
			makeFile(HIGHSCORES, "Highscores.txt");
		}
		else bIsInitialFileGood = true;
	}while (!bIsInitialFileGood);
}

void Menu::makeInitialFiles()
{
	makeFile(HIGHSCORES, "Highscores.txt");
}

void Menu::makeFile(std::string _DIRpath, std::string strFileName)
{
	std::string _path = _DIRpath + strFileName;
	std::ofstream filePlace;
	std::cout << "Creating " << strFileName << " at " << _DIRpath << std::endl;
	filePlace.open(_path);
	filePlace.close();
}

bool Menu::lookForFile(std::string _DIRpath, std::string strFileName)
{
	std::string _path = _DIRpath + strFileName;
	std::ifstream fileCheck;
	fileCheck.open(_path);
	if (!fileCheck.is_open())
	{
		std::cout << strFileName << " has not been found at: " << _path << std::endl;
		return false;
	}
	else fileCheck.close();
	return true;
}


/*The following methods are used to validate wether or not essential directories exists*/

struct stat info;

// Creates directory
void Menu::makeDir(int fileType)
{
	std::string _exBatFile = MAKE_FILES;
	switch (fileType)
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
	_exBatFile += " >nul"; // This is used to not display logs from cmdlet
	system(_exBatFile.c_str());
}

// Sends different queries to check
void Menu::checkEssentialDirectories()
{
	checkDir(HIGHSCORES);
	checkDir(DETAILED_RECORDS);
	checkDir(PROBLEM_SET);
}

// Functions checks and makes files found missing
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
				makeDir(3);
			else { std::cout << "Unknown error orccured.\n"; system("exit"); }
		}
	} while (!bDoesDirExists);
}
// Function checks if specific Dir exists using stat info
bool Menu::lookForDir(std::string _DIRpath)
{
	if (stat(_DIRpath.c_str(), &info) != 0) // If dir was found succesfully return 0 if not returns -1
	{
		std::cout << "Cannot access " << _DIRpath << "\n";
		return false;
	}
	std::cout << _DIRpath << " found!\n";
	return true;
}
