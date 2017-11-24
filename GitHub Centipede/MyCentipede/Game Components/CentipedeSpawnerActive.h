#ifndef _CentipedeSpawnerActive
#define _CentipedeSpawnerActive

#include "CentipedeSpawnerStrategy.h"

class CentipedeSpawnerActive : public CentipedeSpawnerStrategy
{
public:
	CentipedeSpawnerActive() { itr = 0; };
	virtual void Spawn(CentipedeSpawner* cs) override;

private:
	int itr;
};

#endif