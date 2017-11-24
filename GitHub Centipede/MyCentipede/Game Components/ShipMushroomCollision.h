#ifndef _ShipMushroomCollision
#define _ShipMushroomCollision

class Ship;

class ShipMushroomCollision
{
public:
	ShipMushroomCollision() {};
	~ShipMushroomCollision() {};

	virtual void Collide(Ship* s) const = 0;

protected:


};

#endif