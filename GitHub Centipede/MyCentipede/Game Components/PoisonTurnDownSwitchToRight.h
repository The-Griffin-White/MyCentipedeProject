#ifndef _PoisonTurnDownSwitchToRight
#define _PoisonTurnDownSwitchToRight

#include "MoveState.h"

class PoisonTurnDownSwitchToRight : public MoveState
{
public:
	PoisonTurnDownSwitchToRight() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif