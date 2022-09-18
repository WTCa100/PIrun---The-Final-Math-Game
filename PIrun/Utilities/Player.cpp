#pragma once
#include"Player.h"

int Player::getLatestId()
{
	if (isInitialLaunch)
		nID = 1;
	else
	{
		nID = getHighestId() + 1;
	}
	std::cout << nID << std::endl;
	return 0;
}

int Player::getHighestId()
{
	std::vector<int> vecsIdList;
	std::string _DIR = SCORES;
	std::string _fileName = SCOREBOARD_CSV;
	std::ifstream loadIDs;
	std::string strLine;
	char cDelimeter = ',';
	loadIDs.open(_DIR + '/' + _fileName);
	while (std::getline(loadIDs, strLine))
	{
		if (strLine == "ID,Name,Points") continue;
		std::stringstream RawLine(strLine);
		std::string RawData;
		bool isFirstCell = true;
		while (std::getline(RawLine, RawData, cDelimeter))
		{
			if (isFirstCell) vecsIdList.push_back(std::stoi(RawData));
			else break;
			isFirstCell = false;
		}
	}
	loadIDs.close();
	if (vecsIdList.empty()) return 0;
	return *std::max_element(vecsIdList.begin(), vecsIdList.end());
}

void Player::getInitialUserName()
{
	do
	{
		std::cout << "Enter your username:\n";
		std::getline(std::cin, this->strUsername);
		if (Validate::isEntryEmpty(this->strUsername))
			std::cout << "Nickname must be at least 1 character long!\n";

	} while (Validate::isEntryEmpty(this->strUsername));
}

void Player::ShowPlayerDetails()
{
	std::cout << "ID: " << nID << std::endl;
	std::cout << "Name: " << strUsername << std::endl;
	std::cout << "Number of problems solved: " << nGameAmmount << " - " << nGoodGameAmmount <<" of games were correct\n";
	std::cout << std::setprecision(2) << std::fixed << "Ratio: " << nGoodGameAmmount / nGameAmmount << std::endl;
	std::cout << "Points collected " << dbPointsEarned << std::endl;
}

void Player::ShowPlayerScoreboard()
{
	std::cout << nID << ": " << strUsername << " got " << dbPointsEarned << " points.\n";
}

double Player::GiveFinalScores()
{
	return this->dbPointsEarned;
}

void Player::SavePlayerDetails(std::fstream& filePtr)
{
	filePtr << this->nID << "," << this->strUsername << "," << this->nGameAmmount << ',' << this->nGoodGameAmmount << ',' << this->dbPointsEarned << std::endl;
}

void Player::SavePlayerProgress(std::ofstream &filePtr)
{
	for (auto i = ProblemSet.begin(); i != ProblemSet.end(); i++)
	{
		i->second.SaveProblem(filePtr);
	}
}

void Player::SavePlayerToScoreboard(std::fstream& filePtr)
{
	filePtr << this->nID << "," << this->strUsername << "," << this->dbPointsEarned << std::endl;
}

int Player::givePlayerId()
{
	return this->nID;
}

void Player::DisplayProblems()
{
	for (auto i = ProblemSet.begin(); i != ProblemSet.end(); i++)
	{
		std::cout << i->first << ": ";
		i->second.showProblemDone();
	}
}


void Player::AssignProblem(Problem currentProblem)
{
	this->ProblemSet.insert(std::make_pair(currentProblem.nProblemId, currentProblem));
	this->nGameAmmount++;
	if (currentProblem.IsAnsGood())
		nGoodGameAmmount++;
}

void Player::AddPoint(int dbPointValue)
{
	this->dbPointsEarned += dbPointValue;
}

Player::Player()
{
	this->ProblemSet.clear();
	this->dbPointsEarned = -1;
	this->isInitialLaunch = 0;
	this->nID = -1;
	this->nGameAmmount = -1;
	this->nGoodGameAmmount = -1;
	this->strUsername = "Dummy";
}

Player::Player(bool isInitial)
{
	this->ProblemSet.clear();
	this->isInitialLaunch = isInitial;
	getLatestId();
	getInitialUserName();
	std::cout << "Hello " << this->strUsername << "!\n Your id is: " << this->nID << "\n";
}

Player::Player(int id, std::string un, double points)
{
	this->nID = id;
	this->strUsername = un;
	this->dbPointsEarned = points;
	this->isInitialLaunch = false;
	this->ProblemSet.clear();
}

Player::Player(int id, std::string un, int nAmt, int nGAmt, double points)
{
	this->nID = id;
	this->strUsername = un;
	this->nGameAmmount = nAmt;
	this->nGoodGameAmmount = nGAmt;
	this->dbPointsEarned = points;
	this->isInitialLaunch = false;
	this->ProblemSet.clear();
}

bool operator<(Player const& P1, Player const& P2)
{
	return P1.dbPointsEarned < P2.dbPointsEarned;
}

bool operator==(Player const& P1, Player const& P2)
{
	return P1.nID == P2.nID;
}
