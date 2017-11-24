#include "WaveLoader.h"

#include "Constants.h"

static const int Default_Critter_Cap = 1;
static const int Default_Critter_Prob = 1000;

WaveLoader::WaveLoader()
{
	centipede = true;
	soloHead = false;
	numCentipedeSegments = Default_Centipede_Segments;
	fleas = false;
	mushroomsToSpawnFlea = Default_Mushrooms_To_Spawn_Fleas;
	fleaCap = Default_Critter_Cap;
	scorpions = false;
	scorpionCap = Default_Critter_Cap;
	scorpionProbability = Default_Critter_Prob;
	spiders = false;
	spiderCap = Default_Critter_Cap;
	spiderProbability = Default_Critter_Prob;
}

WaveLoader::WaveLoader(bool spawnCentipede, bool spawnFleas, bool spawnScorpions, bool spawnSpiders)
{
	centipede = spawnCentipede;
	soloHead = false;
	numCentipedeSegments = Default_Centipede_Segments;
	fleas = spawnFleas;
	mushroomsToSpawnFlea = Default_Mushrooms_To_Spawn_Fleas;
	fleaCap = Default_Critter_Cap;
	scorpions = spawnScorpions;
	scorpionCap = Default_Critter_Cap;
	scorpionProbability = Default_Critter_Prob;
	spiders = spawnSpiders;
	spiderCap = Default_Critter_Cap;
	spiderProbability = Default_Critter_Prob;
}
WaveLoader::WaveLoader(bool spawnCentipede, bool spawnSoloHead, int numSegments,
	bool spawnFleas, int numMushrooms, int numFleaCap,
	bool spawnScorpions, int scorpProb, int scorpCap,
	bool spawnSpiders, int spiderProb, int numSpiderCap)
{
	centipede = spawnCentipede;
	soloHead = spawnSoloHead;
	numCentipedeSegments = numSegments;
	fleas = spawnFleas;
	mushroomsToSpawnFlea = numMushrooms;
	fleaCap = numFleaCap;
	scorpions = spawnScorpions;
	scorpionProbability = scorpProb;
	scorpionCap = scorpCap;
	spiders = spawnSpiders;
	spiderProbability = spiderProb;
	spiderCap = numSpiderCap;
}

bool WaveLoader::SpawnCentipede() 
{
	return centipede;
}

bool WaveLoader::SpawnSoloHead()
{
	return soloHead;
}

int WaveLoader::NumberSegments()
{
	return numCentipedeSegments;
}

bool WaveLoader::SpawnFleas()
{
	return fleas;
}

int WaveLoader::NumberMushroomsToSpawnFleas()
{
	return mushroomsToSpawnFlea;
}

int WaveLoader::FleaCapNumber()
{
	return fleaCap;
}

bool WaveLoader::SpawnScorpions() 
{
	return scorpions;
}

int WaveLoader::ScorpionCapNumber()
{
	return scorpionCap;
}

int WaveLoader::ScorpionProbabilityNumber()
{
	return scorpionProbability;
}

bool WaveLoader::SpawnSpiders()
{
	return spiders;
}

int WaveLoader::SpiderCapNumber()
{
	return spiderCap;
}

int WaveLoader::SpiderProbabilityNumber()
{
	return spiderProbability;
}