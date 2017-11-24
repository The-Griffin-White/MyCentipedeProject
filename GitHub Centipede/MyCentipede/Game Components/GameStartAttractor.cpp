#include "GameStartAttractor.h"

#include "GameQuitToAttractor.h"

void GameStartAttractor::Switch()
{
	PlayerManager::SwitchToPlayer();
}