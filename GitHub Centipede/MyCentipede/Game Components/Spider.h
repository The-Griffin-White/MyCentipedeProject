#ifndef _Spider
#define _Spider

#include "Constants.h"

class Bullet;
class MushroomField;			// Skipping this and using collision for now
class SpiderState;
enum Direction;

class Spider : public GameObject
{
public:
	Spider();

	void Initialize(Direction d);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

	sf::Vector2f GetPos();
	float GetY();
	float GetX();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	const SpiderState *pCurrentState;

	int itr;
	int cellItr;
	int row;
	int col;
};

#endif