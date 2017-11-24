#ifndef _Scorpion
#define _Scorpion

#include "Constants.h"
#include "Direction.h"

class Bullet;
class Mushroom;
class ScorpionStrategy;

class Scorpion : public GameObject
{
public:
	Scorpion();

	void Initialize(int row, Direction d);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	int itr;
	int row;
	int col;

	ScorpionStrategy* left;
	ScorpionStrategy* right;
	ScorpionStrategy* move;
};

#endif