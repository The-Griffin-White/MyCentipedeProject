#ifndef _FSMCentipede
#define _FSMCentipede

#include "Constants.h"

class MoveState;
class MoveFSM;
class FSMCentipedeBody;
class Bullet;

enum Direction;
enum class Obstacle;

class FSMCentipede : public GameObject
{
public:
	void TestKill();

	FSMCentipede();
	~FSMCentipede();

	virtual void Initialize(int r, int c);

	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

	void Rotate(float a);
	sf::Vector2f GetPos();

	void NextToRight();
	void NextToLeft();
	void NextToUp();
	void NextToDown();

	void UpdateRowAndCol();

	void SetFollower(FSMCentipedeBody* f);
	const MoveState* GetCommand();
	void SendCommand(const MoveState* c);
	void SendCommand();
	void TakeRowAndColumn(int r, int c);

	int GetIterator();
	void Iterate();
	void ResetIterator();

	virtual void Collision(GameObject *other) {};
	virtual void Collision(Bullet *other);

	virtual void ReportDeath() { };

protected:
// Sprite values
	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap* bitmap;

// Nav Values
	int row;
	int col;
	int nextRow;
	int nextCol;
	const MoveState* pCurrentState;
	int itr;

// Other stuff
	sf::Vector2f Pos;
	FSMCentipedeBody* follower;

};

#endif