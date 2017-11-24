#ifndef _Mushroom
#define _Mushroom

#include "Constants.h"

class Bullet;
class MushroomField;
class Spider;

class Mushroom : public GameObject
{
public:
	Mushroom();

	void Initialize(sf::Vector2f p, MushroomField* g, int i, int j);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision( GameObject *go){};
	virtual void Collision( Bullet *other );
//	virtual void Collision( Spider *other );

	void MushroomEaten();
	void MakePoison();
	void RemoveFromGrid();
	void ChangeMushroomSprite();
	bool IsMushroomHurt();
	void MakeNonPoison();
	void Heal(int amount);

	sf::Vector2f GetPos();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	int health;
	int MAXHEALTH;
	int spriteValue;

	MushroomField* grid;
	int x, y;
};

#endif _Asteroid