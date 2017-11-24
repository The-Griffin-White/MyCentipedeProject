#ifndef _FSMCentipedeHead
#define _FSMCentipedeHead

#include "FSMCentipede.h"

class FSMCentipedeHead : public FSMCentipede
{
public:
	FSMCentipedeHead();

	void Initialize(int r, int c, Direction lr, Direction ud);
	void Initialize(sf::Vector2f p, int row, int nextRow, int col, int nextCol, const MoveState* s, FSMCentipedeBody* f, int i);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	Obstacle Inspect(int r, int c);

	int GetRow();
	int GetColumn();

	void GiveFollowerRowAndColumn();

	void ReachedBottomRow();

	virtual void ReportDeath();

private:

};

#endif