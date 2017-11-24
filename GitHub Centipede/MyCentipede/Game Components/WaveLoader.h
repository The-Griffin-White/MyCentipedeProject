#ifndef _WaveLoader
#define _WaveLoader

/// Used to store information to spawn new waves
class WaveLoader
{
public:
	WaveLoader();
	WaveLoader(bool spawnCentipede, bool spawnFleas, bool spawnScorpions, bool spawnSpiders);
	WaveLoader(bool spawnCentipede, bool soloHead, int numSegments, 
				bool spawnFleas, int numMushrooms, int fleaCap, 
				bool spawnScorpions, int scorpProb, int scorpCap,
				bool spawnSpiders, int spiderProb, int spiderCap);

	bool SpawnCentipede();
	bool SpawnSoloHead();
	int NumberSegments();
	bool SpawnFleas();
	int NumberMushroomsToSpawnFleas();
	int FleaCapNumber();
	bool SpawnScorpions();
	int ScorpionCapNumber();
	int ScorpionProbabilityNumber();
	bool SpawnSpiders();
	int SpiderCapNumber();
	int SpiderProbabilityNumber();

private:
	bool centipede;
	bool soloHead;
	int numCentipedeSegments;
	bool fleas;
	int mushroomsToSpawnFlea;
	int fleaCap;
	bool scorpions;
	int scorpionCap;
	int scorpionProbability;
	bool spiders;
	int spiderCap;
	int spiderProbability;

};

#endif