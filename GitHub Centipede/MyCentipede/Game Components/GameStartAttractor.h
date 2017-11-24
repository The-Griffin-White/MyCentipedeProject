#ifndef _GameStartAttractor
#define _GameStartAttractor

#include "GameStartStrategy.h"

class GameStartAttractor : public GameStartStrategy
{
public:
	virtual void Switch() override;
};

#endif