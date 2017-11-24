#ifndef _ScorpionSpawner
#define _ScorpionSpawner

#include "TEAL\CommonElements.h"

class SpawnerUpdate;

class ScorpionSpawner : public GameObject
{
public:
	ScorpionSpawner();
	~ScorpionSpawner();

	void Initialize();
	void Initialize(int probability, int maxNumScorpions);

	virtual void Update();
	virtual void Draw() {};
	virtual void Destroy();

	void GiveFactoryCap();
	void MaxNumReached();
	void BelowMaxNum();

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

private:
	SpawnerUpdate* pUpdate;
	SpawnerUpdate* pInactive;
	SpawnerUpdate* pActive;
	int spawnChance;
	int scorpionCap;

};

#endif