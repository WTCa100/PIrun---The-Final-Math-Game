#pragma once
#include <string>

#include"MaxValues.h"
#include"../Pathing/Paths.h"
#include"../InputValidator/InputCheck.h"
#include"../../ProblemGen.h"
#include"../../Player.h"

class GameState
{
private:
	static void makeDir(int fileType);
	static void checkEssentialDirectories();
	static void checkDir(std::string _FILENAME);
	static bool lookForDir(std::string _DIRpath);
	void initializeGame();
public:
	int GameDifficulty, GameAmmount;
	void GetDifficultyLevel();
	void GetGameAmmount();
	static bool InitialBootUp;
	static void Setup();
	GameState();
};