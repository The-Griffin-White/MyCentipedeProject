#ifndef _AttractorMovementCollection
#define _AttractorMovementCollection

#include "AttractorOffsetArray.h"

class AttractorMovementCollection
{
public:
	// I want the attractor to remain closer to the center than normally allowed in play, since it looks better
	static const float AttractorWindowHeightTop;
	static const float AttractorWindowHeightBot;
	static const float AttractorWindowWidthMax;
	static const float AttractorWindowWidthMin;


	static const AttractorOffsetArray OffsetsLeftDownDiagonal;
	static const AttractorOffsetArray OffsetsRightDownDiagonal;
	static const AttractorOffsetArray OffsetsLeftDown;
	static const AttractorOffsetArray OffsetsRightDown;
	static const AttractorOffsetArray OffsetsLeftUp;
	static const AttractorOffsetArray OffsetsRightUp;
	static const AttractorOffsetArray OffsetsLeftUpDiagonal;
	static const AttractorOffsetArray OffsetsRightUpDiagonal;
};

#endif