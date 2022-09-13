#pragma once
#include"Menu.h"

int Menu::GetGameDiff()
{
	std::string strTmpHolder;
	std::cout << "Choose your difficulty: \n";
	std::cout << "Option 1\n";
	std::cout << "Option 2\n";
	std::cout << "Option 3\n";
	std::cout << "Option 4\n";
	std::cout << "Option 5\n";
	std::cout << "Option 6\n";
	do
	{
		std::getline(std::cin, strTmpHolder);
	} while (true);
	return 0;
}

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
// Main and default constructor
Menu::Menu()
{
	GameState::Setup();
	InitialBootUp = GameState::InitialBootUp;
	std::cout << "GameState::InitialBootUp = " << GameState::InitialBootUp << "\n";
	if (InitialBootUp)
		makeInitialFiles();
	else
	{
		checkEssentialFiles();
	}
	setInitialDiff();
	
	system("Pause");
	system("cls");
}
void Menu::setInitialDiff()
{
	this->nGameDiff = 1;
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
	checkScores(HIGHSCORES_TXT);
	checkScores(SCOREBOARD_CSV);
}

void Menu::makeInitialFiles()
{
	makeFile(SCORES, HIGHSCORES_TXT);
}

void Menu::checkScores(std::string strFileName, std::string _DIRpath)
{
	bool bIsFileGood;
	do
	{
		if (!lookForFile(SCORES, strFileName))
		{
			bIsFileGood = false;
			makeFile(SCORES, strFileName);
		}
		else
			bIsFileGood = true;
		 
	} while (!bIsFileGood);
}

void Menu::makeFile(std::string _DIRpath, std::string strFileName)
{
	std::string _path = _DIRpath + strFileName;
	std::ofstream filePlace;
	std::cout << "Creating " << strFileName << " at " << _DIRpath << std::endl;
	filePlace.open(_path);
	if (strFileName == SCOREBOARD_CSV)
		filePlace << "ID," << "Name," << "Points\n";
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

/*Display functions and methods*/

void Menu::showAboutMeSection()
{
	std::cout << "About the game\n";
}

void Menu::showHighScores()
{
	std::cout << "Highscores section\n";
}
