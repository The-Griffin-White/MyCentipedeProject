#ifndef _SpawnerUpdate
#define _SpawnerUpdate

class SpawnerUpdate
{
public:
	SpawnerUpdate() {};
	virtual bool GetUpdate(int probability) = 0;
};

#endif