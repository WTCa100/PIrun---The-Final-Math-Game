#include"Gamestate.h"

struct stat info;

bool GameState::InitialBootUp;


std::vector<Player> GameState::populateVectorWithHighscores(std::map<int, Player> getFrom)
{
	std::vector<Player> vecsOut;
	for (auto i = getFrom.begin(); i != getFrom.end(); i++)
		vecsOut.push_back(i->second);
	return vecsOut;
}

bool GameState::addToHighScores(Player checkPlayer)
{
	std::map<int, Player> mappedHighscores = GameState::loadPlayersHighscores();
	if (mappedHighscores.size() < 10)
		return true;
	return checkPlayer.GiveFinalScores() > GameState::highestScore(mappedHighscores);
}

bool GameState::comparePlayers(std::pair<int, Player> a, std::pair<int, Player> b)
{
	return a < b;
}

void GameState::addPlayerToHighScores(Player P1, std::map<int, Player> mappedHighscores)
{
	int nPosition = 1;
	bool bIsPositionLast = false;
	Player* PrevPosition = new Player;
	// If the size of mappedHighscores is lower than 10
	if (mappedHighscores.size() < 10)
	{
		std::vector<Player> vecsHighscores = populateVectorWithHighscores(mappedHighscores); // Save scores into a vector in the same order

		mappedHighscores.clear(); // Remove values from mapped highscores
		for (int i = 0; i < vecsHighscores.size(); i++)
		{
			if (i == vecsHighscores.size() - 1) { vecsHighscores.push_back(P1); break; } // Do the checking
			else
			{
				if (i == 0) { if (vecsHighscores[i] < P1) { vecsHighscores.insert(vecsHighscores.begin(), P1); break; } }
				else
				{
					if (P1 < vecsHighscores[i] && vecsHighscores[i - 1] < P1) { vecsHighscores.insert(vecsHighscores.begin() + i, P1); return; }
				}
			}
		}
		if (vecsHighscores.empty())
			vecsHighscores.push_back(P1);
		if (vecsHighscores.size() > 10) // If its bigger than 10 delete last element
			vecsHighscores.pop_back();
		for (int i = 0; i < vecsHighscores.size(); i++) // repopulate mappedHighscores
		{
			mappedHighscores.insert(std::make_pair(i + 1, vecsHighscores[i]));
		}
	}
	// If the size of mappedHighscores is greater or equalt to 10
	else
	{
		for (auto i = mappedHighscores.begin(); i != mappedHighscores.end(); i++)
		{
			if (nPosition == 1)
			{
				if (i->second < P1){mappedHighscores[nPosition] = P1; break;}
			}
			else
			{
				if (P1 < PrevPosition && i->second < P1)
				{
					if (i->second < P1) { mappedHighscores[nPosition] = P1; break; }
				}
			}
			nPosition++;
			PrevPosition = &i->second;
		}
	}
	delete PrevPosition;
	saveNewHighscores(mappedHighscores);
}

void GameState::saveNewHighscores(std::map<int, Player> newMappedHighscores)
{
	std::string _DIR = SCORES;
	std::string _fileName = HIGHSCORES_CSV;
	std::ofstream highscoresFile;
	highscoresFile.open(_DIR + '/' + _fileName);
	if (!highscoresFile.is_open()) { std::cout << "No such file!\n"; return; }
	highscoresFile << "Place,Name,ID,Points" << std::endl;
	for (auto& i : newMappedHighscores)
	{
		highscoresFile << i.first << ',';
		i.second.SavePlayerToHighscores(highscoresFile);
	}
}

double GameState::highestScore(std::map<int, Player>& checkHighscores)
{
	return checkHighscores[1].GiveFinalScores();
}

std::map<int, Player> GameState::loadPlayersHighscores()
{
	std::map <int, Player> mapOut;
	std::string _DIR = SCORES;
	std::string _fileName = HIGHSCORES_CSV;
	std::ifstream highscoresLoad;
	std::string strLine;
	char cDelimeter = ',';
	highscoresLoad.open(_DIR + "/" + _fileName);
	if (!highscoresLoad.is_open()) { std::cout << "No such file!\n"; return mapOut; }
	while (std::getline(highscoresLoad, strLine))
	{
		if (strLine == "Place,Name,ID,Points") continue;
		int nCell = 1;
		int *nPlace = new int;
		std::string rawData;
		// Constructor comp.
		std::string* tmpUsername = new std::string;
		int* tmpId = new int; double* tmpPoints = new double;
		// Get those values
		std::stringstream ssRow(strLine);
		while (std::getline(ssRow, rawData, cDelimeter))
		{
			switch (nCell)
			{
			case 1:
				*nPlace = std::stoi(rawData);
				break;
			case 2:
				*tmpUsername = rawData;
				break;
			case 3:
				*tmpId = std::stoi(rawData);
				break;
			case 4:
				*tmpPoints = std::stod(rawData);
				break;
			}
			if (nCell == 4)
			{
				Player* tmpPlayer = new Player(*tmpId, *tmpUsername, *tmpPoints);
				mapOut.insert(std::make_pair(*nPlace, *tmpPlayer));
				delete tmpPlayer;
				delete nPlace; delete tmpUsername; delete tmpId; delete tmpPoints;
			}
			else nCell++;
		}
	}
	return mapOut;
}

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

Player GameState::returnPlayer(int id)
{
	std::map<int, Player> tmpMap = LoadDetails();
	return tmpMap[id];
}

void GameState::displayPset(Player PDisp)
{
	PDisp.DisplayProblems();
}

void GameState::SearchForPlayerPset(Player& PSearchFor)
{
	std::string _DIR = PROBLEM_SET;
	std::string _fileName = std::to_string(PSearchFor.givePlayerId()) + ".txt";
	std::ifstream loadDetails;
	std::string strLine;
	int nLine = 1;
	loadDetails.open(_DIR + "/" + _fileName);
	if (!loadDetails.is_open()) { std::cout << "No such file!\n"; return; }
	// Constructor tmp value holders
	int *tmpId = new int; 
	double* tmpComp1 = new double; double* tmpComp2 = new double; double* tmpExp = new double; double* tmpActual = new double; double* tmpPoints = new double;
	char* tmpAct = new char;
	bool* tmpCor = new bool;
	while (std::getline(loadDetails, strLine))
	{
		switch (nLine)
		{
		case 1:
			*tmpId = std::stoi(strLine);
			break;
		case 2:
			*tmpPoints = std::stod(strLine);
			break;
		case 3:
			*tmpComp1 = std::stod(strLine);
			break;
		case 4:
			*tmpAct = strLine[0];
			break;
		case 5:
			*tmpComp2 = std::stod(strLine);
			break;
		case 6:
			*tmpExp = std::stod(strLine);
			break;
		case 7:
			*tmpActual = std::stod(strLine);
			break;
		case 8:
			*tmpCor = std::stoi(strLine);
			break;
		}
		if (nLine == 8)
		{
			Problem* tmpProb = new Problem(*tmpId, *tmpPoints, *tmpComp1, *tmpAct, *tmpComp2, *tmpExp, *tmpActual, *tmpCor);
			PSearchFor.AssignProblem(*tmpProb);
			delete tmpProb;
			nLine = 1;
		}
		else nLine++;
	}
	delete tmpAct; delete tmpActual; delete tmpComp1; delete tmpComp2; delete tmpCor; delete tmpExp; delete tmpId; delete tmpPoints;
	loadDetails.close();
}

void GameState::LookAndDisplayPlayerDetails(std::map<int, Player> mappedPlayers, int Id)
{
	auto getPlayerInfo = mappedPlayers.find(Id);
	if (getPlayerInfo == mappedPlayers.end()) { std::cout << "No such player found!\n"; return; }
	mappedPlayers[Id].ShowPlayerDetails();
}

std::map<int,Player> GameState::LoadDetails()
{
	std::map<int, Player> mapOut;
	std::string _DIR = DETAILED_RECORDS;
	std::string _fileName = DETAILS_CSV;
	std::ifstream detailFile;
	std::string strLine;
	char cDelimeter = ',';
	detailFile.open(_DIR + '/' + _fileName);
	if (!detailFile.is_open()) { std::cout << "Cannot load file.\n";}
	while (std::getline(detailFile, strLine))
	{
		if (strLine == "ID,Name,Number_of_Problems,Problems_Solved_Good,Points") continue;
		int nCell = 1;
		std::stringstream ssRow(strLine);
		std::string rawData;
		// Constructor tmp data holders
		int* tmpId = new int; int* tmpProblemAmmount = new int; int* tmpProblemGoodAmmount = new int;
		std::string* tmpUserName = new std::string;
		double* tmpPoints = new double;
		// Distinct info
		while (std::getline(ssRow, rawData, cDelimeter))
		{
			switch (nCell)
			{
			case 1: *tmpId = std::stoi(rawData); break;
			case 2: *tmpUserName = rawData; break;
			case 3: *tmpProblemAmmount = std::stoi(rawData); break;
			case 4: *tmpProblemGoodAmmount = std::stoi(rawData); break;
			case 5: *tmpPoints = std::stod(rawData); break;
			}
			if (nCell == 5)
			{
				Player* tmpP = new Player(*tmpId, *tmpUserName, *tmpProblemAmmount, *tmpProblemGoodAmmount, *tmpPoints);
				mapOut.insert(std::make_pair(tmpP->givePlayerId(), *tmpP));
				delete tmpP;
				delete tmpId; delete tmpUserName; delete tmpPoints; delete tmpProblemGoodAmmount; delete tmpProblemAmmount;
				nCell = 1;
			}
			else nCell++;
		}
	}
	detailFile.close();
	return mapOut;
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

// Make the game

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
	system("cls");
	gameSummary(*MathPlayer);
	system("cls");
	system("Pause");
	MathPlayer->DisplayProblems();
	saveProblem(*MathPlayer);
	savePlayerStats(*MathPlayer, 1);
	savePlayerStats(*MathPlayer, 2);
	if (GameState::addToHighScores(*MathPlayer))
		GameState::addPlayerToHighScores(*MathPlayer, GameState::loadPlayersHighscores());
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
void GameState::savePlayerStats(Player whoToSign, int _Type)
{
	std::string _saveDIR;
	std::string _saveFile;
	switch (_Type)
	{
	case 1:
		_saveDIR = SCORES;
		_saveFile = SCOREBOARD_CSV;
		break;
	case 2:
		_saveDIR = DETAILED_RECORDS;
		_saveFile = DETAILS_CSV;
	}
	std::fstream savePlayerInfo;
	savePlayerInfo.open(_saveDIR + '/' + _saveFile, std::ios::app);
	switch (_Type)
	{
	case 1:
		whoToSign.SavePlayerToScoreboard(savePlayerInfo);
		break;
	case 2:
		whoToSign.SavePlayerDetails(savePlayerInfo);
		break;
	}
	savePlayerInfo.close();

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
