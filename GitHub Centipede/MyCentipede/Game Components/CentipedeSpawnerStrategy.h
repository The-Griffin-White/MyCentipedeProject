#ifndef _CentipedeSpawnerStrategy
#define _CentipedeSpawnerStrategy

class CentipedeSpawner;

class CentipedeSpawnerStrategy
{
public:
	virtual void Spawn(CentipedeSpawner* cs) = 0;

};

#endif