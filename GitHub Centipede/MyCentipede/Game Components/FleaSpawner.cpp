#include "FleaSpawner.h"

#include "FleaFactory.h"
#include "SpawnerActive.h"
#include "SpawnerInactive.h"

#include "Player\PlayerManager.h"

FleaSpawner::FleaSpawner()
{
	pInactive = new SpawnerInactive;
	pActive = new SpawnerActive;
}

void FleaSpawner::Initialize(int maxNumFleas)
{
	spawnChance = 600;
	fleaCap = maxNumFleas;

	pUpdate = pActive;

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events

	GiveFactoryCap();
}

void FleaSpawner::Initialize()
{
	ConsoleMsg::WriteLine("Using default FleaSpawner, should not be happening");
	spawnChance = 600;
	fleaCap = 1;

	pUpdate = pActive;
	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events

	GiveFactoryCap();
}

void FleaSpawner::Update()
{
	if (pUpdate->GetUpdate(spawnChance))
	{
		ConsoleMsg::WriteLine("Spawning Flea");
		FleaFactory::CreateFlea();
	}
}

void FleaSpawner::GiveFactoryCap()
{
	FleaFactory::GetSpawnerPointer(this);
	FleaFactory::GetMaxNumFleas(fleaCap);
}

void FleaSpawner::MaxNumReached()
{
	pUpdate = pInactive;
}

void FleaSpawner::BelowMaxNum()
{
	pUpdate = pActive;
}

void FleaSpawner::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	// Flea
	if (k == sf::Keyboard::Num1)
	{
		FleaFactory::CreateFlea();
	}
}

void FleaSpawner::Destroy()
{
	FleaFactory::GetSpawnerPointer(nullptr);
	pUpdate = pInactive;
	DeregisterInput();
}

FleaSpawner::~FleaSpawner()
{
	if (pInactive) delete pInactive;
	if (pActive) delete pActive;
}