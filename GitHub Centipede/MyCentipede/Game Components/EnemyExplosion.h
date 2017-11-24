#ifndef _EnemyExplosion
#define _EnemyExplosion

#include "Constants.h"

class EnemyExplosion : public GameObject
{
public:
	EnemyExplosion();

	void Initialize(sf::Vector2f p);

	virtual void Update();
	virtual void Draw();

private:
	AnimatedSprite MainSprite;

	sf::Vector2f Pos;
};


#endif _Explosion