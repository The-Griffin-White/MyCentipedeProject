#ifndef _CentipedeSpawnerInactive
#define _CentipedeSpawnerInactive

#include "CentipedeSpawnerStrategy.h"

class CentipedeSpawnerInactive : public CentipedeSpawnerStrategy
{
public:
	virtual void Spawn(CentipedeSpawner* cs) override {};

};

#endif