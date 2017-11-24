#include "PlayerOneHUDStrategy.h"

#include "../HUD/HUDManager.h"

void PlayerOneHUDStrategy::UpdateScore(int val)
{
	HUDManager::UpdateScore(val);
}

void PlayerOneHUDStrategy::UpdateLives(int val)
{
	HUDManager::UpdateLives(val);
}