#ifndef _TurnUpSwitchToLeft
#define _TurnUpSwitchToLeft

#include "MoveState.h"

class TurnUpSwitchToLeft : public MoveState
{
public:
	TurnUpSwitchToLeft() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif