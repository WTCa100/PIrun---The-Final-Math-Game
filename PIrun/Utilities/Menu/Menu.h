#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<sys/stat.h>
#include<string>
#include<sstream>

#include"InputValidator/InputCheck.h"
#include"Pathing/Paths.h"

class Menu
{
private:
	// Checking Files
	void getUserInput(int& actType);
	void checkEssentialFiles();
	void makeInitialFiles();
	void checkScores(std::string strFileName, std::string _DIRpath = SCORES);
	void makeFile(std::string _DIRpath, std::string strFileName);
	bool lookForFile(std::string _DIRpath, std::string strFileName = "");
	// Checking Directories
	void makeDir(int fileType);
	void checkEssentialDirectories();
	void checkDir(std::string _FILENAME);
	bool lookForDir(std::string _DIRpath);
	// Display Functions
	void showAboutMeSection();
	void showHighScores();
protected:
	bool InitialBootUp;
public:
	// Display functions
	void mainDisplay();
	Menu();
};
