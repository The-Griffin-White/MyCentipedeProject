#ifndef _FleaStrategy
#define _FleaStrategy

#include "TEAL\CommonElements.h"

class Flea;

class FleaStrategy
{
public:
	FleaStrategy() {};
	virtual sf::Vector2f Move(Flea* f) const = 0;
	virtual void DropMushroom(Flea* f) const = 0;
	virtual void NextState(Flea* f, int row) const = 0;
	virtual void FleaHit(Flea* f) const = 0;

};

#endif