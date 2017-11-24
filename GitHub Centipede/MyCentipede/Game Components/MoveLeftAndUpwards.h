#ifndef _MoveLeftAndUpwards
#define _MoveLeftAndUpwards

#include "MoveState.h"

class MoveLeftAndUpwards : public  MoveState
{
public:
	MoveLeftAndUpwards() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif