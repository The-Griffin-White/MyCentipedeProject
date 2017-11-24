#ifndef _SpiderMovementCollection
#define _SpiderMovementCollection

#include "SpiderOffsetArray.h"

class SpiderMovementCollection
{
public:
	static const SpiderOffsetArray OffsetsLeftDownDiagonal;
	static const SpiderOffsetArray OffsetsRightDownDiagonal;
	static const SpiderOffsetArray OffsetsLeftDown;
	static const SpiderOffsetArray OffsetsRightDown;
	static const SpiderOffsetArray OffsetsLeftUp;
	static const SpiderOffsetArray OffsetsRightUp;
	static const SpiderOffsetArray OffsetsLeftUpDiagonal;
	static const SpiderOffsetArray OffsetsRightUpDiagonal;
};

#endif