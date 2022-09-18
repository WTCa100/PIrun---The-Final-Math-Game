#pragma once
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include"MaxValues.h"
#include"../Pathing/Paths.h"
#include"../InputValidator/InputCheck.h"
#include"../../ProblemGen.h"
#include"../../Player.h"

class GameState
{
private:
	// Loading scores
	// TODO: Load highscores into the memory.
	static std::vector<Player> populateVectorWithHighscores(std::map<int, Player> getFrom);
	static bool addToHighScores(Player checkPlayer);
	static void addPlayerToHighScores(Player P1, std::map<int, Player> mappedHighscores);
	static std::map<int, Player> loadPlayersHighscores();
	static double highestScore(std::map<int, Player>& checkHighscores);
	// Checking Directories
	static void makeDir(int fileType);
	static void checkEssentialDirectories();
	static void checkDir(std::string _FILENAME);
	static bool lookForDir(std::string _DIRpath);
	// Actual gameplay
	void initializeGame();
	void gameSummary(Player whoPlayed);
	// Saving scores
	void saveProblem(Player whoPlayed);
	static void saveNewHighscores(std::map<int, Player> newMappedHighscores);
	static void savePlayerStats(Player whoToSign, int _Type);
public:
	// Loading scores, details and Psets
	static void LoadScoreboards();
	static void SearchForPlayerPset(Player& PSearchFor);
	static Player returnPlayer(int id);
	static void LookAndDisplayPlayerDetails(std::map<int, Player> mappedPlayers, int Id);
	static std::map<int,Player> LoadDetails();
	// Display functions
	static void displayPset(Player PDisp);
	// Get values
	int GameDifficulty, GameAmmount;
	void GetDifficultyLevel();
	void GetGameAmmount();
	// Initial boot up functions
	static bool InitialBootUp;
	static void Setup();
	// Actual gameplay
	GameState();
};