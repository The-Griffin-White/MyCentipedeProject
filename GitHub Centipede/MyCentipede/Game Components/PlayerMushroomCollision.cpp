#include "PlayerMushroomCollision.h"
#include "Ship.h"

void PlayerMushroomCollision::Collide(Ship* s) const
{
	s->LastPos();
}