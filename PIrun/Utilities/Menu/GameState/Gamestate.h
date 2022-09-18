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
	static bool addToHighScores(Player checkPlayer);
	static bool comparePlayers(std::pair<int, Player> a, std::pair<int, Player> b);
	static void addPlayerToHighScores(Player P1, std::map<int, Player> mappedHighscores);
	static void saveNewHighscores(std::map<int, Player> newMappedHighscores);
	static std::map<int, Player> loadPlayersHighscores();
	static double highestScore(std::map<int, Player>& checkHighscores);
	static void makeDir(int fileType);
	static void checkEssentialDirectories();
	static void checkDir(std::string _FILENAME);
	static bool lookForDir(std::string _DIRpath);
	void initializeGame();
	void saveProblem(Player whoPlayed);
	static void savePlayerStats(Player whoToSign, int _Type);
	void gameSummary(Player whoPlayed);
public:
	static Player returnPlayer(int id);
	static void displayPset(Player PDisp);
	static void SearchForPlayerPset(Player& PSearchFor);
	static void LookAndDisplayPlayerDetails(std::map<int, Player> mappedPlayers, int Id);
	static std::map<int,Player> LoadDetails();
	static void LoadScoreboards();
	int GameDifficulty, GameAmmount;
	void GetDifficultyLevel();
	void GetGameAmmount();
	static bool InitialBootUp;
	static void Setup();
	GameState();
};