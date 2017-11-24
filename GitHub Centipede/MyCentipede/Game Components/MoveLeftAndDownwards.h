#ifndef _MoveLeftAndDownwards
#define _MoveLeftAndDownwards

#include "MoveState.h"

class MoveLeftAndDownwards : public MoveState
{
public:
	MoveLeftAndDownwards() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif