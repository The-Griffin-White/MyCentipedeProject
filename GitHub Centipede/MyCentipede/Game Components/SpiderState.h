#ifndef _SpiderState
#define _SpiderState

// Abstract Spider State class

struct SpiderOffsetArray;
class Spider;

class SpiderState
{
public:
	SpiderState() {};

	const SpiderOffsetArray* GetMoveOffsets() const { return pMoveOffsets; }
	virtual const SpiderState* GetNextState(Spider* pSpider) const = 0;
	virtual const int NextRow() const = 0;
	virtual const int NextCol() const = 0;

protected:
	const SpiderOffsetArray* pMoveOffsets;
};

#endif