#ifndef _AttractorStateLeftDownDiagonal
#define _AttractorStateLeftDownDiagonal

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateLeftDownDiagonal : public AttractorState
{
public:
	AttractorStateLeftDownDiagonal();

	virtual const AttractorState* GetNextState() const override;
};

#endif