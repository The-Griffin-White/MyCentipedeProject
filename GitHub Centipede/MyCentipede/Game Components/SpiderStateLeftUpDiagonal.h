#ifndef _SpiderStateLeftUpDiagonal
#define _SpiderStateLeftUpDiagonal

#include "SpiderState.h"

/// Spider is moving Straight down, on left-moving track. 
/// We can either continue, go up, go diagonal-up, or diagonal-down
class SpiderStateLeftUpDiagonal : public SpiderState
{
public:
	SpiderStateLeftUpDiagonal();

	virtual const SpiderState* GetNextState(Spider* pSpider) const override;
	virtual const int NextRow() const override { return -1; };
	virtual const int NextCol() const { return -1; };
};

#endif