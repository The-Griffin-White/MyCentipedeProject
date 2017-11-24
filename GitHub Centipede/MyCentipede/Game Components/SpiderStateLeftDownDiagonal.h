#ifndef _SpiderStateLeftDownDiagonal
#define _SpiderStateLeftDownDiagonal

#include "SpiderState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class SpiderStateLeftDownDiagonal : public SpiderState
{
public:
	SpiderStateLeftDownDiagonal();

	virtual const SpiderState* GetNextState(Spider* pSpider) const override;
	virtual const int NextRow() const override { return 1; };
	virtual const int NextCol() const { return -1; };
};

#endif