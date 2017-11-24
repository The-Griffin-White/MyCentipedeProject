#ifndef _MovementCollection
#define _MovementCollection

#include "OffsetArray.h"

class MovementCollection
{
public:
	static const OffsetArray OffsetsStraightRight[];
	static const OffsetArray OffsetsTurnUpEndRight[];
	static const OffsetArray OffsetsTurnDownEndRight[];
	static const OffsetArray OffsetsStraightLeft[];
	static const OffsetArray OffsetsTurnUpEndLeft[];
	static const OffsetArray OffsetsTurnDownEndLeft[];
	static const OffsetArray OffsetsPoisonTurnDownEndLeft[];
	static const OffsetArray OffsetsPoisonTurnDownEndRight[];

	static const float RotationStraightLeft[];
	static const float RotationStraightRight[];
	static const float RotationDownLeft[];
	static const float RotationDownRight[];
	static const float RotationUpLeft[];
	static const float RotationUpRight[];
};

#endif