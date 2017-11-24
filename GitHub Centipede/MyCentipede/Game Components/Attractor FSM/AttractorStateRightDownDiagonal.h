#ifndef _AttractorStateRightDownDiagonal
#define _AttractorStateRightDownDiagonal

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateRightDownDiagonal : public AttractorState
{
public:
	AttractorStateRightDownDiagonal();

	virtual const AttractorState* GetNextState() const override;
};

#endif