#ifndef _TurnUpSwitchToRight
#define _TurnUpSwitchToRight

#include "MoveState.h"

class TurnUpSwitchToRight : public  MoveState
{
public:
	TurnUpSwitchToRight() {};
	virtual const OffsetArray* GetMoveOffsets(const int i) const;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const override;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const override;
};

#endif