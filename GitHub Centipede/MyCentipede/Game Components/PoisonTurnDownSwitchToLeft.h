#ifndef _PoisonTurnDownSwitchToLeft
#define _PoisonTurnDownSwitchToLeft

#include "MoveState.h"

class PoisonTurnDownSwitchToLeft : public MoveState
{
public:
	PoisonTurnDownSwitchToLeft() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif