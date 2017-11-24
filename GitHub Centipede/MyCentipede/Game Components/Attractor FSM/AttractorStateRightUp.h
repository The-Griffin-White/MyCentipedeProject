#ifndef _AttractorStateRightUp
#define _AttractorStateRightUp

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateRightUp : public AttractorState
{
public:
	AttractorStateRightUp();

	virtual const AttractorState* GetNextState() const override;
};

#endif