#ifndef _SpiderStateLeftDown
#define _SpiderStateLeftDown

#include "SpiderState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class SpiderStateLeftDown : public SpiderState
{
public:
	SpiderStateLeftDown();

	virtual const SpiderState* GetNextState(Spider* pSpider) const override;
	virtual const int NextRow() const override { return 1; };
	virtual const int NextCol() const {	return 0; };
};

#endif