#include "Wave.h"

#include "SpawnerFactory.h"

#include "CentipedeSpawner.h"
#include "FleaSpawner.h"
#include "ScorpionSpawner.h"
#include "SpiderSpawner.h"

#include "Player\PlayerManager.h"

#include "WaveLoader.h"

/// Creates an empty wave (no spawners)
Wave::Wave()
{
	pCentipedeSpawner = nullptr;
	waitingOnFleaSpawn = false;
	pFleaSpawner = nullptr;
	pScorpionSpawner = nullptr;
	pSpiderSpawner = nullptr;
}

/// Initializes a wave with 4 standard spawners, selected with booleans
void Wave::Initialize(bool spawnCentipedes, bool spawnFleas, bool spawnScorpions, bool spawnSpiders)
{
	if (spawnCentipedes)
	{
		pCentipedeSpawner = SpawnerFactory::CreateCentipedeSpawner();
	}
	if (spawnFleas)
	{
		waitingOnFleaSpawn = true;
	}
	if (spawnScorpions)
	{
		pScorpionSpawner = SpawnerFactory::CreateScorpionSpawner();
	}
	if (spawnSpiders)
	{
		pSpiderSpawner = SpawnerFactory::CreateSpiderSpawner();
	}
}

/// Initializes a wave with 4 standard spawners, selected with the WaveLoader class
void Wave::Initialize(WaveLoader* data)
{
	if (data->SpawnCentipede())
	{
		pCentipedeSpawner = SpawnerFactory::CreateCentipedeSpawner(data->SpawnSoloHead(), data->NumberSegments());
	}
	else
	{
		pCentipedeSpawner = nullptr;
	}
	if (data->SpawnFleas())
	{
		waitingOnFleaSpawn = true;
		PlayerManager::MushroomsToStartFleaSpawn(data->NumberMushroomsToSpawnFleas());
		fleaCap = data->FleaCapNumber();
	}
	else
	{
		waitingOnFleaSpawn = false;
	}
	if (data->SpawnScorpions())
	{
		pScorpionSpawner = SpawnerFactory::CreateScorpionSpawner(data->ScorpionProbabilityNumber(), data->ScorpionCapNumber());
	}
	else
	{
		pScorpionSpawner = nullptr;
	}
	if (data->SpawnSpiders())
	{
		pSpiderSpawner = SpawnerFactory::CreateSpiderSpawner(data->SpiderProbabilityNumber(), data->SpiderCapNumber());
	}
	else
	{
		pSpiderSpawner = nullptr;
	}
}

void Wave::StartFleaSpawn()
{
	if (!pFleaSpawner && waitingOnFleaSpawn)
		pFleaSpawner = SpawnerFactory::CreateFleaSpawner(fleaCap);
}

Wave::~Wave()
{
	if (pCentipedeSpawner) pCentipedeSpawner->MarkForDestroy();
	if (pFleaSpawner) pFleaSpawner->MarkForDestroy();
	if (pScorpionSpawner) pScorpionSpawner->MarkForDestroy();
	if (pSpiderSpawner) pSpiderSpawner->MarkForDestroy();
}

void Wave::KillWave()
{
	if (pCentipedeSpawner) pCentipedeSpawner->MarkForDestroy();
	if (pFleaSpawner) pFleaSpawner->MarkForDestroy();
	if (pScorpionSpawner) pScorpionSpawner->MarkForDestroy();
	if (pSpiderSpawner) pSpiderSpawner->MarkForDestroy();
}