#ifndef _PlayerManager
#define _PlayerManager

#include <stack>
#include "..\TEAL\CommonElements.h"
#include "..\GridSpace.h"

class Player;

class PlayerManager
{
private:
	static PlayerManager *ptrInstance;

	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	PlayerManager& operator=(const PlayerManager&) = delete;
	~PlayerManager();

	static PlayerManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerManager;
		return *ptrInstance;
	}

	/*
	Possibility ->
	Player* pCurrentPlayer
	Player* pAI
	PlayerLinkedListHead* pHead			// Cycle through these for an arbitrary number of human players
	*/
	Player* pCurrentPlayer;
	Player* pPlayerOne;
	Player* pAttractor;

	void privInitialize(Player* p, Player* ai);
	void privSwitchToPlayer();
	void privSwitchToAttractor();

	// Private NON_STATIC methods to perform actual work on member var
	sf::Vector2f privGetShipPos();

	bool privOutOfLives();
	void privRespawnShip();
	void privGoToNextLevel();
	void privLoadLevel();
	void privReloadLevel();
	void privIncreaseScore(int val);
	void privResetLevel();
	void privResetLives();
	void privIncrementLevel();
	void privDecrementLives();

	void privRegenMushroomField();
	void privRegenNextMushroom();

	sf::Vector2f privGetCenterCoordinate(int row, int col);
	void privDeleteMushroom(int row, int col);
	void privMakeMushroomPoison(int row, int col);
	Obstacle privInspectCentipedeObstacles(int row, int col);
	void privAddMushroomHere(int row, int col);

	sf::Vector2f privGetPlayerDirections();
	void privGetPlayerFireCommand();
	void privShootBullet();

public:
	static void Initialize(Player* p, Player* ai) { Instance().privInitialize(p, ai); };

	static bool OutOfLives() { return Instance().privOutOfLives(); };

	static sf::Vector2f GetShipPos() { return Instance().privGetShipPos(); };

	static void SwitchToPlayer() { Instance().privSwitchToPlayer(); };
	static void SwitchToAttractor() { Instance().privSwitchToAttractor(); };

	static void RespawnShip() { Instance().privRespawnShip(); };
	static void GoToNextLevel() { Instance().privGoToNextLevel(); };
	static void LoadLevel() { Instance().privLoadLevel(); };
	static void ReloadLevel() { Instance().privReloadLevel(); };
	static void IncreaseScore(int val) { Instance().privIncreaseScore(val); };
	static void ResetLevel() { Instance().privResetLevel(); };
	static void ResetLives() { Instance().privResetLives(); };
	static void IncrementLevel() { Instance().privIncrementLevel(); };
	static void DecrementLives() { Instance().privDecrementLives(); };

	static sf::Vector2f GetCenterCoordinate(int row, int col) { return Instance().privGetCenterCoordinate(row, col); };

	static void MushroomsToStartFleaSpawn(int num);
	static void RegenMushroomField() { Instance().privRegenMushroomField(); };
	static void RegenNextMushroom() { Instance().privRegenNextMushroom(); };
	static void DeleteMushroom(int row, int col) { Instance().privDeleteMushroom(row, col); };
	static void MakeMushroomPoison(int row, int col) { Instance().privMakeMushroomPoison(row, col); };
	static Obstacle InspectCentipedeObstacles(int row, int col) { return Instance().privInspectCentipedeObstacles(row, col); };
	static void AddMushroomHere(int row, int col) { Instance().privAddMushroomHere(row, col); };
	static void EatMushroom(int row, int col);

	static sf::Vector2f GetPlayerDirections() { return Instance().privGetPlayerDirections(); };
	static void GetPlayerFireCommand() { Instance().privGetPlayerFireCommand(); };
	static void ShootBullet() { Instance().privShootBullet(); };

	static void Terminate();
};

#endif