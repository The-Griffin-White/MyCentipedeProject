// Explosion
// Andre Berthiaume, March 2013

#ifndef _PlayerExplosion
#define _PlayerExplosion

#include "Constants.h"

class PlayerExplosion : public GameObject
{
public:
	PlayerExplosion();
	
	void Initialize(sf::Vector2f p);

	virtual void Update();
	virtual void Draw();

private:
	AnimatedSprite MainSprite;

	sf::Vector2f Pos;
};


#endif _Explosion