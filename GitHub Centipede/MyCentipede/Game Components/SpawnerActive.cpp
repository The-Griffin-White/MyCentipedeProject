#include "SpawnerActive.h"

#include "Constants.h"

bool SpawnerActive::GetUpdate(int probability)
{
	if (rand() % probability == 1)
	{
		return true;
	}
	return false;
}