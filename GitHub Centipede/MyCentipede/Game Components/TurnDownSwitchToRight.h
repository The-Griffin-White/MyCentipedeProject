#ifndef _TurnDownSwitchToRight
#define _TurnDownSwitchToRight

#include "MoveState.h"

class TurnDownSwitchToRight : public  MoveState
{
public:
	TurnDownSwitchToRight() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif