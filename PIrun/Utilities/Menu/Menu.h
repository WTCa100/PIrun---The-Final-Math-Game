#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<sys/stat.h>
#include<string>
#include<sstream>

#include"GameState/Gamestate.h"
#include"GameState/MaxValues.h"
#include"InputValidator/InputCheck.h"
#include"Pathing/Paths.h"

class Menu
{
private:
	// Value obtaining
	void setInitialDiff(); // Constructor method that sets initial difficult value to 1
	// Checking Files
	void getUserInput(int& actType);
	void checkEssentialFiles();
	void makeInitialFiles();
	void checkScores(std::string strFileName, std::string _DIRpath = SCORES);
	void makeFile(std::string _DIRpath, std::string strFileName);
	bool lookForFile(std::string _DIRpath, std::string strFileName = "");
	// Display Functions
	void newGame();
	void showAboutMeSection();
	void showScoreboard();
	void showHighScores();
protected:
	bool InitialBootUp;
	int nGameDiff;
public:
	// Value obtaining
	int GetGameDiff();
	// Display functions
	void mainDisplay();
	Menu();
};
