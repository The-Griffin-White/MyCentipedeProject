#ifndef _ScorpionRightStrategy
#define _ScorpionRightStrategy

#include "ScorpionStrategy.h"
#include "Constants.h"

class ScorpionRightStrategy : public ScorpionStrategy
{
public:
	float GetMovement() override { return Scorpion_Speed; };
	int NextCol() override { return 1; };
};

#endif