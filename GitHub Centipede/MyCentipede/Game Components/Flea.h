#ifndef _Flea
#define _Flea

#include "Constants.h"

class Bullet;
class FleaStrategy;

class Flea : public GameObject
{
public:
	Flea();
	~Flea();

	void Initialize(int col);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

	int GetIterator();
	void Iterate();
	void ResetIterator();

	int GetRow();

	void DropMushrooms();
	void NextRow();
	void ActivateFlea();
	void DeactivateFlea();
	void SetFleaHurt();
	void KillFlea();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

	const FleaStrategy* pCurrMovement;

	int health;
	int MAXHEALTH;

	int row;
	int col;

	int itr;
};
#endif