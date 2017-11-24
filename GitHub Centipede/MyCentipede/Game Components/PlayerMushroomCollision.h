#ifndef _PlayerMushroomCollision
#define _PlayerMushroomCollision

#include "ShipMushroomCollision.h"

class PlayerMushroomCollision : public ShipMushroomCollision
{
public:
	PlayerMushroomCollision() {};
	~PlayerMushroomCollision() {};

	virtual void Collide(Ship* s) const;

private:


};

#endif