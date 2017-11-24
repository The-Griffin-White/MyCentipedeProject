#ifndef _GameQuitToAttractor
#define _GameQuitToAttractor

#include "GameStartStrategy.h"

class GameQuitToAttractor : public GameStartStrategy
{
public:
	virtual void Switch() override;
};

#endif