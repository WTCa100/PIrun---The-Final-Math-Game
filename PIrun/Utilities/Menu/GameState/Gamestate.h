#pragma once
#include <string>

#include"../Pathing/Paths.h"
#include"../InputValidator/InputCheck.h"

class GameState
{
private:
	static void makeDir(int fileType);
	static void checkEssentialDirectories();
	static void checkDir(std::string _FILENAME);
	static bool lookForDir(std::string _DIRpath);
public:
	static bool InitialBootUp;
	static void Setup();
};