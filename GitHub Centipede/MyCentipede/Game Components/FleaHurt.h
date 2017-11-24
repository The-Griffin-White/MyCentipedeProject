#ifndef _FleaHurt
#define _FleaHurt

#include "FleaStrategy.h"

class FleaHurt : public FleaStrategy
{
public:
	virtual sf::Vector2f Move(Flea* f) const override;
	virtual void DropMushroom(Flea* f) const override {};
	virtual void NextState(Flea* f, int row) const override;
	virtual void FleaHit(Flea* f) const override;

};

#endif