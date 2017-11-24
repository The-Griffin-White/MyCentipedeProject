#ifndef _SpawnerInactive
#define _SpawnerInactive

#include "SpawnerUpdate.h"

class SpawnerInactive : public SpawnerUpdate
{
public:
	SpawnerInactive() {};
	virtual bool GetUpdate(int probability) override { return false; };
};

#endif