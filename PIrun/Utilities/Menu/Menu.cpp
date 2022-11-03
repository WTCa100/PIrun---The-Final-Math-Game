#pragma once
#include"Menu.h"

// Value obtaining

// Checking files

// Display functions

// Sub-menus

// Value obtaining (public)

// Dispay functions (public)

void Menu::mainDisplay()
{
	int nNextActionType;
	do
	{
		std::cout << "Welcome to PIrun - the final math game!\t\tGame created by John Bielawa - (WTCa100/Pepga315)\n";
		std::cout << "Version: 0.3.0v\n";
		std::cout << "Main Menu:\n";
		std::cout << "1. New game\n";
		std::cout << "2. Scoreboard\n";
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
				system("cls");
				newGame();
				break;
			case 2:
				system("cls");
				scoreboardSectionMenu();
				break;
			case 3:
				system("cls");
				showAboutMeSection();
			break;
			case 4:
				exit(0);
			}
	} while (true);
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
	checkScores(HIGHSCORES_CSV);
	checkScores(SCOREBOARD_CSV);
	checkScores(DETAILS_CSV, DETAILED_RECORDS);
}

void Menu::makeInitialFiles()
{
	makeFile(SCORES, HIGHSCORES_CSV);
	makeFile(SCORES, SCOREBOARD_CSV);
	makeFile(DETAILED_RECORDS, DETAILS_CSV);
}

void Menu::checkScores(std::string strFileName, std::string _DIRpath)
{
	bool bIsFileGood;
	do
	{
		if (!lookForFile(_DIRpath, strFileName))
		{
			bIsFileGood = false;
			makeFile(_DIRpath, strFileName);
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
	{
		filePlace << "ID,Name,Points\n";
		filePlace.close();
		return;
	}
	if (strFileName == DETAILS_CSV)
	{
		filePlace << "ID,Name,Number_of_Problems,Problems_Solved_Good,Points" << std::endl;
		filePlace.close();
		return;
	}
	if (strFileName == HIGHSCORES_CSV)
	{
		filePlace << "Place,Name,ID,Points" << std::endl;
		filePlace.close();
		return;
	}
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

void Menu::newGame()
{
	GameState* GState = new GameState;

	delete GState; // Remove this later
}

void Menu::showProblemList(int checkID)
{
	Player ThisPlayerProblem = GameState::returnPlayer(checkID);
	GameState::SearchForPlayerPset(ThisPlayerProblem);
	ThisPlayerProblem.DisplayProblems();
	return;
}

void Menu::showPlayerDetail(int checkID)
{
	bool bWasPlayerFound = GameState::LookAndDisplayPlayerDetails(GameState::LoadDetails(), checkID);
	char nextAction;
	std::string tmpValHolder;
	if (bWasPlayerFound)
	{
		do
		{
			std::cout << "Would you like to see his list of problems? [y/n]\n";
			std::getline(std::cin, tmpValHolder);
			if (!Validate::isYesNoValid(tmpValHolder)) std::cout << "Please enter valid option\n" << std::endl;
		} while (!Validate::isYesNoValid(tmpValHolder));
		nextAction = std::toupper(tmpValHolder[0]);
		tmpValHolder.clear();
		if (nextAction == 'Y')
		{
			showProblemList(checkID);
			system("pause");
		}
	}
	else system("pause");
	return;
}

void Menu::scoreboardSectionMenu()
{
	std::string strTmpDataHolder;
	do
	{
		std::cout << "-=Scoreboards=-\n";
		showScoreboard();
		std::cout << "If you want to see detailed player record input player ID\n";
		std::cout << "If you want to see highscores type \"Highscores\" or simply \"h\"\n";
		std::cout << "If you want to go back to main menu type \"Exit\" or simply press enter\n";
		std::getline(std::cin, strTmpDataHolder);
		if (!(strTmpDataHolder.empty() || Validate::MakeUpper(strTmpDataHolder) == "EXIT"))
		{
			if (Validate::isInputNumber(strTmpDataHolder))
			{
				showPlayerDetail(std::stoi(strTmpDataHolder));
				system("cls");
			}
			else
			{
				if (strTmpDataHolder == "HIGHSCORES" || std::toupper(strTmpDataHolder[0]) == 'H')
				{
					system("cls");
					std::cout << "-=HighScores=-\n";
					showHighScores();
					system("cls");
				}
				else { std::cout << "Enter a valid option\n"; system("pause"); system("cls"); };
			}
		}
	} while (!(strTmpDataHolder.empty() || Validate::MakeUpper(strTmpDataHolder) == "EXIT"));
	system("cls");
}

void Menu::showAboutMeSection()
{
	std::cout << "3.14run or PiRun is a game based on my original idea from february 2022.\n";
	std::cout << "This is was my very first attempt to make functional game or something that is game-like.\n";
	std::cout << "The first version of PiRun was and still is called \"SimpleMathGame\" - it was the original name!\n";
	std::cout << "Then there was SimpleMathGameV2 and SimpleMathGame-Rework and yet here we are at 3.14run\n";
	std::cout << "The first version of the game was very simple hence the name. \nThe idea was that the program will generate random number from various ranges depending on choosen difficulty.\n";
	std::cout << "The first version only did this, it didn't even save your scores.\n";
	std::cout << "The second version was just like the first one but with classes and user-defined headers.\n";
	std::cout << "Then the third version which was the \"LAST REWORK\" came and definetly wasn't the last rework!\n";
	std::cout << "Why? Well simply it was bad and I didn't feel like it should be the very last thing I do to this game.\n";
	std::cout << "The Third edition of the game included file saving, interactive scoreboards and more features \nsuch as using doubles and floats as user input (yes in previous versions you couldn't have non-devidable numbers!)\n";
	std::cout << "But it was spaghetti codded (this is also kind of spahgetti but not as much), \nand some of the problem handling I made just aren't good enough for me anymore.\n";
	std::cout << "THAT IS WHY i made 3.14run or PiRun, it is because I wanted to make something looking more professional and I think that I did it. \nUnlike the previous games, in this one I used every single thing I knew about programming in C++\n";
	if (InitialBootUp)
		std::cout << "Have fun playing the game newcomer!\n";
	else
		std::cout << "Anyway let's have some fun playing the game shall we?\n";
	system("pause");
	system("cls");
}

void Menu::showScoreboard()
{
	std::cout << "Format: ID : User name got (point ammount) points.\n";
	GameState::displayScoreboard();
}

void Menu::showHighScores()
{
	GameState::displayHighscores();
	system("pause");
	system("cls");
}
