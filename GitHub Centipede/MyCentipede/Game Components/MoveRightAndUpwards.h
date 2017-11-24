#ifndef _MoveRightAndUpwards
#define _MoveRightAndUpwards

#include "MoveState.h"

class MoveRightAndUpwards : public  MoveState
{
public:
	MoveRightAndUpwards() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif