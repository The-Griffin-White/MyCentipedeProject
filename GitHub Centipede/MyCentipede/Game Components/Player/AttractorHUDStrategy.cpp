#include "AttractorHUDStrategy.h"

#include "../MushroomField.h"

#include "../HUD/HUDManager.h"

void AttractorHUDStrategy::MenuHUD(MushroomField* g)
{
	HUDManager::CreateAttractorHUD(g);
}