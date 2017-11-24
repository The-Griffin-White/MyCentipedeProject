#ifndef _AttractorStateRightDown
#define _AttractorStateRightDown

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateRightDown : public AttractorState
{
public:
	AttractorStateRightDown();

	virtual const AttractorState* GetNextState() const override;
};

#endif