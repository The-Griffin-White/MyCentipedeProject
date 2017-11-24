#ifndef _SpawnerActive
#define _SpawnerActive

#include "SpawnerUpdate.h"

class SpawnerActive : public SpawnerUpdate
{
public:
	SpawnerActive() {};
	virtual bool GetUpdate(int probability) override;
};

#endif