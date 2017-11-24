#ifndef _ScorpionLeftStrategy
#define _ScorpionLeftStrategy

#include "ScorpionStrategy.h"
#include "Constants.h"

class ScorpionLeftStrategy : public ScorpionStrategy
{
public:
	float GetMovement() override { return -Scorpion_Speed; };
	int NextCol() override { return -1; };
};

#endif