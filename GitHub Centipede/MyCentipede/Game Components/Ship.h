// Ship
// Andre Berthiaume, Aug 2012

#ifndef _Ship
#define _Ship

#include "TEAL\CommonElements.h"

// Forward declarations
class Mushroom;
class FSMCentipedeHead;
class FSMCentipedeBody;
class Flea;
class Spider;
class ShipMushroomCollision;

class Ship : public GameObject
{
public:
	Ship();
	~Ship();

	void Initialize();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	void ShootBullet();
	void LastPos();
	
	virtual void Collision( GameObject *other ){};
	virtual void Collision( Mushroom *other);
	virtual void Collision( FSMCentipedeHead *other);
	virtual void Collision( FSMCentipedeBody *other);
	virtual void Collision( Flea *other);
	virtual void Collision( Spider *other);

	sf::Vector2f GetPos();

private:
	float offset;

	sf::Vector2f Pos;
	sf::Vector2f PrevPos;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;

	const ShipMushroomCollision* collider;

};

#endif _Ship