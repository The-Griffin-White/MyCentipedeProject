#include "CentipedeSpawner.h"

#include "FSMCentipedeFactory.h"

#include "Player/PlayerManager.h"
#include "CentipedeSpawnerActive.h"
#include "CentipedeSpawnerInactive.h"

#include "Constants.h"

CentipedeSpawner::CentipedeSpawner()
{
	updater = nullptr;
}

void CentipedeSpawner::Initialize(bool spawnSoloHead, int numSegments)
{
	soloHead = spawnSoloHead;
	segments = numSegments;
	FSMCentipedeFactory::GetSpawnerPointer(this);
	updater = new CentipedeSpawnerActive;
	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
}

void CentipedeSpawner::Initialize()
{
	soloHead = false;
	segments = Default_Centipede_Segments;
	FSMCentipedeFactory::GetSpawnerPointer(this);
	updater = new CentipedeSpawnerActive;
	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
}

void CentipedeSpawner::Update()
{
	updater->Spawn(this);
}

void CentipedeSpawner::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{
	if (k == sf::Keyboard::Return)
	{
//		FSMCentipedeFactory::CreateCentipede(-1, 16, segments);
		FSMCentipedeFactory::CreateSoloHeadFromPlayerArea();
	}
}

void CentipedeSpawner::SpawnCentipede()
{
	FSMCentipedeFactory::CreateCentipede(-1, 16, segments);
	if (soloHead)
		SpawnSoloHead();
}

void CentipedeSpawner::SpawnSoloHead()
{
	FSMCentipedeFactory::CreateSoloHeadFromTop();
}

void CentipedeSpawner::GoInactive()
{
	delete updater;
	updater = new CentipedeSpawnerInactive;
}

void CentipedeSpawner::Destroy()
{
	FSMCentipedeFactory::GetSpawnerPointer(nullptr);
	DeregisterInput();
}