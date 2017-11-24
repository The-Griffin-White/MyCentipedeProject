#ifndef _CentipedeSpawner
#define _CentipedeSpawner

#include "TEAL\CommonElements.h"

class CentipedeSpawnerStrategy;

class CentipedeSpawner : public GameObject
{
public:
	CentipedeSpawner();

	void Initialize();
	void Initialize(bool spawnSoloHead, int numSegments);

	virtual void Update();
	virtual void Draw() {};
	virtual void Destroy();
	
	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);

	void SpawnCentipede();
	void SpawnSoloHead();
	void GoInactive();

private:
	CentipedeSpawnerStrategy* updater;
	bool soloHead;
	int segments;
};

#endif