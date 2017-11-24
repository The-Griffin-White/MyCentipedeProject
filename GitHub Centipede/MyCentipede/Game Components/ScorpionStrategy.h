#ifndef _ScorpionStrategy
#define _ScorpionStrategy

class ScorpionStrategy
{
public:
	virtual float GetMovement() = 0;
	virtual int NextCol() = 0;
};

#endif