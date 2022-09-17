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
	double GiveFinalScores(); // Only use this method at the end of gameplay
	void SavePlayerDetails(std::ofstream& filePtr);
	void SavePlayerProgress(std::ofstream &filePtr);
	void SavePlayerToScoreboard(std::fstream& filePtr); // Todo save player to scoreboard.csv
	int givePlayerId();
	void DisplayProblems(); // Debug
	void AssignProblem(Problem currentProblem);
	void AddPoint(int dbPointValue);
	Player(bool isInitial);
	Player(int id, std::string un, double points); // Scoreboard.csv loading constructor
};