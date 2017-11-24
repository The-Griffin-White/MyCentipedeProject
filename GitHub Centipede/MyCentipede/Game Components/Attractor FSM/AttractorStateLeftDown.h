#ifndef _AttractorStateLeftDown
#define _AttractorStateLeftDown

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateLeftDown : public AttractorState
{
public:
	AttractorStateLeftDown();

	virtual const AttractorState* GetNextState() const override;
};

#endif