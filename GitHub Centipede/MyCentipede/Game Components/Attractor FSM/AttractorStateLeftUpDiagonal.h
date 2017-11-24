#ifndef _AttractorStateLeftUpDiagonal
#define _AttractorStateLeftUpDiagonal

#include "AttractorState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class AttractorStateLeftUpDiagonal : public AttractorState
{
public:
	AttractorStateLeftUpDiagonal();

	virtual const AttractorState* GetNextState() const override;
};

#endif