#pragma once
#include<string>
#include<fstream>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include<sstream>
#include<algorithm>

#include "Menu/InputValidator/InputCheck.h"
#include "Menu/Pathing/Paths.h"
#include "ProblemGen.h"

class Player
{
private:
	std::map <int, Problem> ProblemSet;
	double dbPointsEarned;
	bool isInitialLaunch;
	int nID, nGameAmmount, nGoodGameAmmount;
	std::string strUsername;
	int getLatestId(); // Obtain the ID value to give to the latest player
	int getHighestId();
	void getInitialUserName(); // Constructor - get player nickname info
public:
	void ShowPlayerDetails();
	void ShowPlayerScoreboard();
	void ShowPlayerHighscores();
	double GiveFinalScores(); // Only use this method at the end of gameplay
	void SavePlayerDetails(std::fstream& filePtr);
	void SavePlayerProgress(std::ofstream &filePtr);
	void SavePlayerToScoreboard(std::fstream& filePtr); // Todo save player to scoreboard.csv
	void SavePlayerToHighscores(std::ofstream& filePtr);
	int givePlayerId();
	void DisplayProblems(); // Debug
	void AssignProblem(Problem currentProblem);
	void AddPoint(int dbPointValue);
	Player(); // Default constructor USE WITH CAUTION
	Player(bool isInitial); // Initializing constructor
	Player(int id, std::string un, double points); // Scoreboard.csv loading constructor
	Player(int id, std::string un, int nAmt, int nGAmt, double points); // Details.csv loading constructor
	friend bool operator<(Player const& P1, Player const& P2); // Sorting purposes
	friend bool operator==(Player const& P1, Player const& P2); // Assigning purposes
};