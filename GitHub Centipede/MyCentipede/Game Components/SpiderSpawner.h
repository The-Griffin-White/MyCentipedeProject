#ifndef _SpiderSpawner
#define _SpiderSpawner

#include "TEAL\CommonElements.h"

class SpawnerUpdate;

class SpiderSpawner : public GameObject
{
public:
	SpiderSpawner();
	~SpiderSpawner();

	void Initialize();
	void Initialize(int probability, int maxNumSpiders);

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
	int spiderCap;

};

#endif