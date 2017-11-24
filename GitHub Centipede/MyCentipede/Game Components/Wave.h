#ifndef _Wave
#define _Wave

class CentipedeSpawner;
class FleaSpawner;
class ScorpionSpawner;
class SpiderSpawner;

class WaveLoader;

class Wave
{
public:
	Wave();
	Wave(const Wave&) = default;
	Wave& operator=(const Wave&) = default;
	~Wave();

	virtual void Initialize(bool spawnCentipedes, bool spawnFleas, bool spawnScorpions, bool spawnSpiders);
	virtual void Initialize(WaveLoader* data);

	void KillWave();

	void StartFleaSpawn();

private:
	CentipedeSpawner* pCentipedeSpawner;
	bool waitingOnFleaSpawn;
	int fleaCap;
	FleaSpawner* pFleaSpawner;
	ScorpionSpawner* pScorpionSpawner;
	SpiderSpawner* pSpiderSpawner;

};

#endif