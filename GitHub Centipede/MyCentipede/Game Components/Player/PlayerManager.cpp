#include "PlayerManager.h"
#include "Player.h"

#include "../GameManager.h"
#include "../HUD/HUDManager.h"

#include "../Audio Manager/AudioManager.h"

PlayerManager* PlayerManager::ptrInstance = nullptr;

/// Initialized the player to null, so remember to Initialize
PlayerManager::PlayerManager()
{
	pCurrentPlayer = nullptr;
}

/// This will break if you don't initialize with whichever player you want to use.
/// Use this to replace the player as well
void PlayerManager::privInitialize(Player* p, Player* ai)
{
	pPlayerOne = p;
	HUDManager::InitializePlayerScore(pPlayerOne->ReturnScore(), pPlayerOne->ReturnLives(), GetCenterCoordinate(-1, 6));
	pAttractor = ai;
	pCurrentPlayer = pAttractor;
	pCurrentPlayer->InitShip();
	pCurrentPlayer->InitMushroomField();
	privLoadLevel();
}

void PlayerManager::privSwitchToPlayer()
{
	if (pCurrentPlayer == pAttractor)
	{
		GameManager::RemoveAllCritters();
		AudioManager::Unmute();
		HUDManager::HideAttractorHUD();
		pAttractor->RemoveShip();
		pAttractor->RemoveMushroomField();
		pCurrentPlayer = pPlayerOne;
		pCurrentPlayer->InitShip();
		pCurrentPlayer->InitMushroomField();
		GameManager::LoadWave(pCurrentPlayer->ReturnLevel());
	}
}

void PlayerManager::privSwitchToAttractor()
{
	if (pCurrentPlayer == pPlayerOne)
	{
		HUDManager::UpdateHighScore(pCurrentPlayer->ReturnGrid(), pCurrentPlayer->ReturnScore());
		GameManager::RemoveAllCritters();
		pCurrentPlayer->ResetScore();
		pCurrentPlayer->ResetLives();
		pCurrentPlayer->RemoveShip();
		pCurrentPlayer->RemoveMushroomField();
		pCurrentPlayer->ResetMushroomField();
		AudioManager::Mute();
		HUDManager::DisplayAttractorHUD();
		pCurrentPlayer = pAttractor;
		pCurrentPlayer->InitMushroomField();
	}
}

/// Clean up our pointer
PlayerManager::~PlayerManager()
{
	ConsoleMsg::WriteLine("deleting playermanager");
	pCurrentPlayer = nullptr;
	if (pPlayerOne) delete pPlayerOne;
	if (pAttractor) delete pAttractor;
}

void PlayerManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void PlayerManager::privRespawnShip()
{
	pCurrentPlayer->InitShip();
}

sf::Vector2f PlayerManager::privGetShipPos()
{
	return pCurrentPlayer->GetShipPos();
}

bool PlayerManager::privOutOfLives()
{
	if (pCurrentPlayer->ReturnLives() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerManager::privLoadLevel()
{
	GameManager::LoadWave(pCurrentPlayer->ReturnLevel());
}

// Everything else just passes to the player
void PlayerManager::privReloadLevel()
{
	GameManager::LoadWave(pCurrentPlayer->ReturnLevel());
}
void PlayerManager::privGoToNextLevel()
{
	pCurrentPlayer->IncrementLevel();
	privLoadLevel();
}

void PlayerManager::privResetLevel()
{
	pCurrentPlayer->ResetLevel();
}

void PlayerManager::privResetLives()
{
	pCurrentPlayer->ResetLives();
}

void PlayerManager::privIncreaseScore(int val)
{
	pCurrentPlayer->IncreaseScore(val);
}
void PlayerManager::privIncrementLevel()
{
	pCurrentPlayer->IncrementLevel();
}
void PlayerManager::privDecrementLives()
{
	pCurrentPlayer->DecrementLives();
}
sf::Vector2f PlayerManager::privGetCenterCoordinate(int row, int col)
{
	return pCurrentPlayer->GetCenterCoordinate(row, col);
}
void PlayerManager::MushroomsToStartFleaSpawn(int num)
{
	Instance().pCurrentPlayer->MushroomsToStartFleaSpawn(num);
}
void PlayerManager::privRegenMushroomField()
{
	pCurrentPlayer->RegenMushroomField();
}
void PlayerManager::privRegenNextMushroom()
{
	pCurrentPlayer->RegenNextMushroom();
}
void PlayerManager::privDeleteMushroom(int row, int col)
{
	pCurrentPlayer->DeleteMushroom(row, col);
}
void PlayerManager::privMakeMushroomPoison(int row, int col)
{
	pCurrentPlayer->MakeMushroomPoison(row, col);
}
Obstacle PlayerManager::privInspectCentipedeObstacles(int row, int col)
{
	return pCurrentPlayer->InspectCentipedeObstacles(row, col);
}
void PlayerManager::privAddMushroomHere(int row, int col)
{
	pCurrentPlayer->AddMushroomHere(row, col);
}
void PlayerManager::EatMushroom(int row, int col)
{
	Instance().pCurrentPlayer->EatMushroom(row, col);
}
sf::Vector2f PlayerManager::privGetPlayerDirections()
{
	return pCurrentPlayer->GetPlayerDirections();
}
void PlayerManager::privGetPlayerFireCommand()
{
	pCurrentPlayer->GetPlayerFireCommand();
}
void PlayerManager::privShootBullet()
{
	pCurrentPlayer->ShootBullet();
}