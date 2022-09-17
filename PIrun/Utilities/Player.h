#pragma once
#include<string>
#include<fstream>
#include <iostream>
#include <map>
#include <fstream>

#include "Menu/InputValidator/InputCheck.h"
#include "Menu/Pathing/Paths.h"
#include "ProblemGen.h"

class Player
{
private:
	std::map <int, Problem> ProblemSet;
	double dbPointsEarned;
	bool isInitialLaunch;
	int nID;
	std::string strUsername;
	int getLatestId(); // Obtain the ID value to give to the latest player
	void getInitialUserName(); // Constructor - get player nickname info
public:
	double GiveFinalScores(); // Only use this method at the end of gameplay
	void SavePlayerProgress(std::ofstream &filePtr);
	void SavePlayerToScoreboard(std::fstream& filePtr); // Todo save player to scoreboard.csv
	int givePlayerId();
	void DisplayProblems(); // Debug
	void AssignProblem(Problem currentProblem);
	void AddPoint(int dbPointValue);
	Player(bool isInitial);
};