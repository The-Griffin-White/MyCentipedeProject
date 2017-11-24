#ifndef _AttractorStateLeftUp
#define _AttractorStateLeftUp

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateLeftUp : public AttractorState
{
public:
	AttractorStateLeftUp();

	virtual const AttractorState* GetNextState() const override;
};

#endif