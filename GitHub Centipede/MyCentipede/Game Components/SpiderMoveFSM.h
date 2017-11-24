#ifndef _SpiderMoveFSM
#define _SpiderMoveFSM

#include "SpiderStateLeftDownDiagonal.h"
#include "SpiderStateRightDownDiagonal.h"
#include "SpiderStateLeftDown.h"
#include "SpiderStateRightDown.h"
#include "SpiderStateLeftUp.h"
#include "SpiderStateRightUp.h"
#include "SpiderStateLeftUpDiagonal.h"
#include "SpiderStateRightUpDiagonal.h"

class SpiderMoveFSM
{
private:

public:
	static const SpiderStateLeftDownDiagonal StateLeftDownDiagonal;
	static const SpiderStateRightDownDiagonal StateRightDownDiagonal;
	static const SpiderStateLeftDown StateLeftDown;
	static const SpiderStateRightDown StateRightDown;
	static const SpiderStateLeftUp StateLeftUp;
	static const SpiderStateRightUp StateRightUp;
	static const SpiderStateLeftUpDiagonal StateLeftUpDiagonal;
	static const SpiderStateRightUpDiagonal StateRightUpDiagonal;
};

#endif