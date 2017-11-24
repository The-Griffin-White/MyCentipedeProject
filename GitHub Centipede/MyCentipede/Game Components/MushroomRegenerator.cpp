#include "MushroomRegenerator.h"
#include "Mushroom.h"

#include "Player\PlayerManager.h"

#include "MushroomRegeneratorFactory.h"

MushroomRegenerator::MushroomRegenerator()
{
	itr = 0;
	casualty = nullptr;
}

void MushroomRegenerator::Initialize(Mushroom* m)
{
	itr = 0;
	casualty = m;
}

void MushroomRegenerator::Update()
{
	if (itr == itrCap)
	{
		casualty->Heal(HealAmount);
		MushroomRegeneratorFactory::ReportMushroomHealed();
		if (!casualty->IsMushroomHurt())				// Mushroom is fully healed...
		{
			MarkForDestroy();
		}
		itr = 0;
	}
	else
	{
		itr++;
	}
}

void MushroomRegenerator::Destroy()
{
	casualty = nullptr;				// Don't delete this, it isn't ours
	PlayerManager::RegenNextMushroom();
}