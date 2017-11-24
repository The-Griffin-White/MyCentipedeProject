#ifndef _AttractorMushroomCollision
#define _AttractorMushroomCollision

#include "ShipMushroomCollision.h"

class AttractorMushroomCollision : public ShipMushroomCollision
{
public:
	AttractorMushroomCollision() {};
	~AttractorMushroomCollision() {};

	virtual void Collide() const {  };

private:


};

#endif