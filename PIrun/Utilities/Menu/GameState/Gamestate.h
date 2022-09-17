#pragma once
#include <string>
#include <fstream>
#include <map>

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
	void saveProblem(Player whoPlayed);
	static void savePlayerStats(Player whoToSign, int _Type);
	void savePlayerDetails(Player whoToSign);
	void gameSummary(Player whoPlayed);
public:
	static void SearchForPlayerPset(int PlayerID);
	static std::map<int,Player> LoadDetails();
	static void LoadScoreboards();
	int GameDifficulty, GameAmmount;
	void GetDifficultyLevel();
	void GetGameAmmount();
	static bool InitialBootUp;
	static void Setup();
	GameState();
};