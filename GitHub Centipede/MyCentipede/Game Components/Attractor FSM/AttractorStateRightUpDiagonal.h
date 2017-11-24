#ifndef _AttractorStateRightUpDiagonal
#define _AttractorStateRightUpDiagonal

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateRightUpDiagonal : public AttractorState
{
public:
	AttractorStateRightUpDiagonal();

	virtual const AttractorState* GetNextState() const override;
};

#endif