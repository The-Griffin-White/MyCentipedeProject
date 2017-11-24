#ifndef _FSMCentipedeBody
#define _FSMCentipedeBody

#include "FSMCentipede.h"

class MoveFSM;

class FSMCentipedeBody : public FSMCentipede
{
public:
	FSMCentipedeBody();

	void Initialize(FSMCentipede* l, int r, int c);

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	void SetLeader(FSMCentipede* l);
	void SetCommand(const MoveState* c);

	void ConvertToHead();

	sf::Vector2f GetPos();
	int GetRow();
	int GetNextRow();
	int GetCol();
	int GetNextCol();
	const MoveState* GetCurrentState();
	FSMCentipedeBody* GetFollower();

	virtual void ReportDeath();

private:
	const MoveState* pNextState;
	FSMCentipede* leader;

};

#endif