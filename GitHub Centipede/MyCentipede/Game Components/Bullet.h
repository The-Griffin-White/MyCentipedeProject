// Bullet
// Andre Berthiaume, Aug 2012

#ifndef _Bullet
#define _Bullet

#include "Constants.h"

//Forward declarations
class Mushroom;
class Ship;
class Flea;
class Scorpion;
class FSMCentipedeHead;
class FSMCentipedeBody;

class Bullet : public GameObject
{
public:
	Bullet();

	void Initialize(sf::Vector2f, Ship* s);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision( GameObject *go){};
	virtual void Collision( Flea *other );
	virtual void Collision( Scorpion *other);
	virtual void Collision( Mushroom *other);
	virtual void Collision( FSMCentipedeHead *other);
	virtual void Collision( FSMCentipedeBody *other);

	sf::Vector2f GetShipPos();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;

	Ship* ship;
};

#endif _Bullet