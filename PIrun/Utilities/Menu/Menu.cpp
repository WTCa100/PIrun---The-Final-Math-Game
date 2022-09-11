#pragma once
#include"Menu.h"

void Menu::mainDisplay()
{
	int nNextActionType;
	do
	{
		std::cout << "Welcome to PIrun - the final math game!\t\tGame created by John Bielawa - (WTCa100/Pepga315)\n";
		std::cout << "Main Menu:\n";
		std::cout << "1. New game\n";
		std::cout << "2. Highscores\n";
		std::cout << "3. About this game\n";
		std::cout << "4. Exit\n";
		std::cout << "Type an option and press enter\n";
		getUserInput(nNextActionType);
		switch (nNextActionType)
			{
			default:
				std::cout << "No such action action found\n";
				break;
			case 1:
				break;
			case 2:
				showHighScores();
				break;
			case 3:
				showAboutMeSection();
			break;
			case 4:
				exit(0);
			}
	} while (nNextActionType != 1);
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
	system("Pause");
	system("cls");
}
// Get user input error handling
void Menu::getUserInput(int &actType)
{
	bool bIsUserInputCorrect = false;
	std::string strTmpUserInput;
	do
	{
		std::getline(std::cin, strTmpUserInput);
		if (!Validate::isInputNumber(strTmpUserInput))
		{
			std::cout << "Please enter a numeric value!\n";
		}
		else
		{
			actType = std::stoi(strTmpUserInput);
			if (!Validate::isWithtinRange(actType, 4, 1))
			{
				std::cout << Validate::isWithtinRange(actType,1,4) << std::endl;
				std::cout << "Please enter value within range!\n";
			}
			else
			{
				bIsUserInputCorrect = true;
			}
		}
			
	} while (!bIsUserInputCorrect);

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
	std::cout << "Looking for " << _path << "\n";
	std::ifstream fileCheck;
	fileCheck.open(_path);
	if (!fileCheck.is_open())
	{
		std::cout << strFileName << " has not been found at: " << _path << std::endl;
		return false;
	}
	else fileCheck.close();
	std::cout << _path << " found!\n";
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
	std::cout << "Looking for: " << _DIRpath << std::endl;
	if (stat(_DIRpath.c_str(), &info) != 0) // If dir was found succesfully return 0 if not returns -1
	{
		std::cout << "Cannot access " << _DIRpath << std::endl;
		return false;
	}
	std::cout << _DIRpath << " found!\n";
	return true;
}

/*Display functions and methods*/

void Menu::showAboutMeSection()
{
	std::cout << "About the game\n";
}

void Menu::showHighScores()
{
	std::cout << "Highscores section\n";
}
