#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<sys/stat.h>
#include<string>

#define HIGHSCORES "Gamestate/"
#define DETAILED_RECORDS "Gamestate/Details"
#define PROBLEM_SET "Gamestate/Details/Problems"

#define MAKE_FILES "Utilities\\Fmake\\"

class Menu
{
private:

	// Checking Directories
	bool InitialBootUp;
	void makeDir(int fileType);
	void checkEssentialDirectories();
	void checkDir(std::string _FILENAME);
	bool lookForDir(std::string _DIRpath);
public:
	void mainDisplay();
	Menu();
};
