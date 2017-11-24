#include "ScorpionSpawner.h"

#include "ScorpionFactory.h"

#include "SpawnerActive.h"
#include "SpawnerInactive.h"

ScorpionSpawner::ScorpionSpawner()
{
	pInactive = new SpawnerInactive;
	pActive = new SpawnerActive;
}

void ScorpionSpawner::Initialize(int probability, int maxNumScorpions)
{
	spawnChance = probability;
	scorpionCap = maxNumScorpions;

	pUpdate = pActive;

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
	
	GiveFactoryCap();
}

void ScorpionSpawner::Initialize()
{
	ConsoleMsg::WriteLine("Using default ScorpionSpawner, should not be happening");
	spawnChance = 600;
	scorpionCap = 1;

	pUpdate = pActive;
	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events

	GiveFactoryCap();
}

void ScorpionSpawner::Update()
{
	if (pUpdate->GetUpdate(spawnChance))
	{
		ScorpionFactory::CreateScorpion();
	}
}

void ScorpionSpawner::GiveFactoryCap()
{
	ScorpionFactory::GetSpawnerPointer(this);
	ScorpionFactory::GetMaxNumScorpions(scorpionCap);
}

void ScorpionSpawner::MaxNumReached()
{
	pUpdate = pInactive;
}

void ScorpionSpawner::BelowMaxNum()
{
	pUpdate = pActive;
}

void ScorpionSpawner::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	// Scorpion
	if (k == sf::Keyboard::Num3)
	{
		ScorpionFactory::CreateScorpion();
	}
}

void ScorpionSpawner::Destroy()
{
	pUpdate = pInactive;
	DeregisterInput();
}

ScorpionSpawner::~ScorpionSpawner()
{
	ScorpionFactory::GetSpawnerPointer(nullptr);
	if (pInactive) delete pInactive;
	if (pActive) delete pActive;
}