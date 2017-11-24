#ifndef _MoveState
#define _MoveState

#include "OffsetArray.h"

class FSMCentipedeHead;
class FSMCentipedeBody;

// ************************************************************
// NEVER declare more than one class per file!
// This is just for prototyping...
//
// WARNING: If I see something like this in your final project, 
// You'll lose a full letter grade!
//
// ************************************************************

class MoveState
{
public:
	MoveState() { };
	virtual const OffsetArray* GetMoveOffsets(const int i) const = 0;
	virtual const MoveState* GetNextHeadState(FSMCentipedeHead* chead) const = 0;
	virtual const MoveState* GetNextBodyState(FSMCentipedeBody* cbody) const = 0;
};

#endif