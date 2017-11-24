#ifndef _TurnDownSwitchToLeft
#define _TurnDownSwitchToLeft

#include "MoveState.h"

class TurnDownSwitchToLeft : public MoveState
{
public:
	TurnDownSwitchToLeft() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif