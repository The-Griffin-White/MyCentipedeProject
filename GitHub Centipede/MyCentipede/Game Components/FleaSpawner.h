#ifndef _FleaSpawner
#define _FleaSpawner

#include "TEAL\CommonElements.h"

class SpawnerUpdate;

class FleaSpawner : public GameObject
{
public:
	FleaSpawner();
	~FleaSpawner();

	void Initialize();
	void Initialize(int maxNumFleas);

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
	int fleaCap;

};

#endif