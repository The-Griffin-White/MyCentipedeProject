#include "CentipedeSpawnerActive.h"

#include "CentipedeSpawner.h"

void CentipedeSpawnerActive::Spawn(CentipedeSpawner* cs)
{
	if (itr == 6)
	{
		cs->SpawnCentipede();
		cs->GoInactive();
	}
	itr++;
}