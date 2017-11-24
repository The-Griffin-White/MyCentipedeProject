#ifndef _MoveRightAndDownwards
#define _MoveRightAndDownwards

#include "MoveState.h"

class MoveRightAndDownwards : public MoveState
{
public:
	MoveRightAndDownwards() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif