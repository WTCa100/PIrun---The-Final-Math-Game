#include"Gamestate.h"

struct stat info;

bool GameState::InitialBootUp;

// Creates directory
void GameState::makeDir(int fileType)
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
void GameState::checkEssentialDirectories()
{
	checkDir(SCORES);
	checkDir(DETAILED_RECORDS);
	checkDir(PROBLEM_SET);
}

// Functions checks and makes files found missing
void GameState::checkDir(std::string _FILENAME)
{
	bool bDoesDirExists = false;
	do
	{
		if (lookForDir(_FILENAME))
			bDoesDirExists = true;
		else
		{
			if (_FILENAME == SCORES)
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
bool GameState::lookForDir(std::string _DIRpath)
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

void GameState::SearchForPlayer(int PlayerID)
{
	std::string _DIR = DETAILED_RECORDS;
	std::string _fileName = DETAILS_CSV;
	std::ifstream loadDetails;
	std::string strLine;
	loadDetails.open(_DIR + "/" + _fileName);
	if (!loadDetails.is_open()) { std::cout << "No such file!\n"; return; }
	// TODO make scores load into the memory
	loadDetails.close();
}

void GameState::LoadScoreboards()
{
	std::string _DIR = SCORES;
	std::string _fileName = SCOREBOARD_CSV;
	std::ifstream ScoreboardFile;
	std::string strLine;
	char cDelimeter = ',';
	ScoreboardFile.open(_DIR + '/' + _fileName);
	if (!ScoreboardFile.is_open()) { std::cout << "No such file!\n"; return; }
	while (std::getline(ScoreboardFile, strLine))
	{
		if (strLine == "ID,Name,Points") continue;
		int nCell = 1;
		std::stringstream ssRow(strLine);
		std::string rawData;
		// Constructor tmp value collectors
		int* tmpId = new int;
		std::string* tmpUserName = new std::string;
		double* tmpPoints = new double;
		while (std::getline(ssRow, rawData, cDelimeter))
		{
			switch (nCell)
			{
			case 1: *tmpId = std::stoi(rawData); break;
			case 2: *tmpUserName = rawData; break;
			case 3: *tmpPoints = std::stod(rawData); break;
			}
			if (nCell == 3)
			{
				Player* tmpP = new Player(*tmpId, *tmpUserName, *tmpPoints);
				tmpP->ShowPlayerScoreboard();
				delete tmpP;
				delete tmpId; delete tmpUserName; delete tmpPoints;
				nCell = 1;
			}
			else nCell++;
		}
	}
	ScoreboardFile.close();
}

// Set up the game 

void GameState::initializeGame()
{
	Player* MathPlayer = new Player(this->InitialBootUp);
	GetDifficultyLevel();
	GetGameAmmount();
	for (int i = 1; i <= this->GameAmmount; i++)
	{
		Problem* Prob = new Problem(this->GameDifficulty, i);
		if (Prob->IsAnsGood()) { MathPlayer->AddPoint(Prob->GiveProblemPointWeight()); }
		MathPlayer->AssignProblem(*Prob);
		delete Prob;
	}
	gameSummary(*MathPlayer);
	system("cls");
	std::cout << "DEBUG: DISPLAY\n";
	system("Pause");
	MathPlayer->DisplayProblems();
	std::cout << "END DEBUG: DISPLAY\n";
	system("Pause");
	system("cls");
	std::cout << "DEBUG: Saving\n";
	std::cout << "saving game files\n";
	saveProblem(*MathPlayer);
	std::cout << "Saved!\n";
	system("Pause");
	std::cout << "DEBUG: SAVING PLAYER INFO\n";
	std::cout << "Saving game files\n";
	savePlayerToScoreboard(*MathPlayer);
	std::cout << "saved!\n";
	system("Pause");
	delete MathPlayer;
}

void GameState::saveProblem(Player whoPlayed)
{
	std::ofstream SaveTxt;
	std::string _saveDIR = PROBLEM_SET;
	_saveDIR += '/' + std::to_string(whoPlayed.givePlayerId()) + ".txt";
	SaveTxt.open(_saveDIR);
	whoPlayed.SavePlayerProgress(SaveTxt);
	SaveTxt.close();
}
void GameState::savePlayerToScoreboard(Player whoToSign)
{
	std::string _saveDIR = SCORES;
	std::string _saveFile = SCOREBOARD_CSV;
	std::fstream saveToScoreboard;
	saveToScoreboard.open(_saveDIR + '/' + _saveFile, std::ios::app);
	whoToSign.SavePlayerToScoreboard(saveToScoreboard);
	saveToScoreboard.close();

}
void GameState::gameSummary(Player whoPlayed)
{
	std::cout << "The game is over!\n";
	std::cout << "You managed to earn " << whoPlayed.GiveFinalScores() << " points" << std::endl;
	system("Pause");
}
// Set up game information
// Difficulty
void GameState::GetDifficultyLevel() 
{
	std::string tmpValHolder;
	bool bIsInputGood;
	do
	{
		std::cout << "Give me difficult level: (from 1 to 6)\n";
		std::getline(std::cin, tmpValHolder);
		if (!Validate::isInputNumber(tmpValHolder))
		{
			std::cout << "The value needs to be numeric!\n";
			bIsInputGood = false;
		}
		else
		{
			if(!Validate::isWithtinRange(std::stoi(tmpValHolder), MAX_DIFF))
			{ 
				std::cout << "Value must be in within 1 to " << MAX_DIFF <<" range!\n";
				bIsInputGood = false;
			}
			else
			{
				bIsInputGood = true;
			}
		}
	} while (!bIsInputGood);
	this->GameDifficulty = std::stoi(tmpValHolder);
	tmpValHolder.clear();
}
// Game ammount (How many games does player wants to play?)
void GameState::GetGameAmmount()
{
	std::string tmpValHolder;
	bool bIsInputGood;
	do
	{
		std::cout << "Give me game ammount (from 1 to 50)\n";
		std::getline(std::cin, tmpValHolder);
		if (!Validate::isInputNumber(tmpValHolder))
		{
			std::cout << "The value needs to be numeric!\n";
			bIsInputGood = false;
		}
		else
		{
			if (!Validate::isWithtinRange(std::stoi(tmpValHolder), MAX_GAME_COUNT))
			{
				std::cout << "Value must be in within 1 to " << MAX_GAME_COUNT << " range!\n";
				bIsInputGood = false;
			}
			else
			{
				bIsInputGood = true;
			}
		}
	} while (!bIsInputGood);
	this->GameAmmount = std::stoi(tmpValHolder);
	tmpValHolder.clear();
}

void GameState::Setup()
{
	checkEssentialDirectories();
}

GameState::GameState()
{
	GameDifficulty = 1; // Initial Value
	initializeGame();
}
