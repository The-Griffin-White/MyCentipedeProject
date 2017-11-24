#include "SpiderSpawner.h"

#include "SpiderFactory.h"
#include "SpawnerActive.h"
#include "SpawnerInactive.h"

SpiderSpawner::SpiderSpawner()
{
	pInactive = new SpawnerInactive;
	pActive = new SpawnerActive;	
}

void SpiderSpawner::Initialize(int probability, int maxNumSpiders)
{
	spawnChance = probability;
	spiderCap = maxNumSpiders;

	pUpdate = pActive;

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events

	GiveFactoryCap();
}

void SpiderSpawner::Initialize()
{
	ConsoleMsg::WriteLine("Using default SpiderSpawner, should not be happening");
	spawnChance = 600;
	spiderCap = 1;

	pUpdate = pActive;
	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events

	GiveFactoryCap();
}

void SpiderSpawner::Update()
{
	if (pUpdate->GetUpdate(spawnChance))
	{
		SpiderFactory::CreateSpider();
	}
}

void SpiderSpawner::GiveFactoryCap()
{
	SpiderFactory::GetSpawnerPointer(this);
	SpiderFactory::GetMaxNumSpiders(spiderCap);
}

void SpiderSpawner::MaxNumReached()
{
	pUpdate = pInactive;
}

void SpiderSpawner::BelowMaxNum()
{
	pUpdate = pActive;
}

void SpiderSpawner::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	// Spider
	if (k == sf::Keyboard::Num2)
	{
		SpiderFactory::CreateSpider();
	}
}

void SpiderSpawner::Destroy()
{
	SpiderFactory::GetSpawnerPointer(nullptr);
	pUpdate = pInactive;
	DeregisterInput();
}

SpiderSpawner::~SpiderSpawner()
{
	if (pInactive) delete pInactive;
	if (pActive) delete pActive;
}