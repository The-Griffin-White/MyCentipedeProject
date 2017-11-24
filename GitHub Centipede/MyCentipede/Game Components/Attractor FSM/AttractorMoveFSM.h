#ifndef _AttractorMoveFSM
#define _AttractorMoveFSM

#include "AttractorStateLeftDownDiagonal.h"
#include "AttractorStateRightDownDiagonal.h"
#include "AttractorStateLeftDown.h"
#include "AttractorStateRightDown.h"
#include "AttractorStateLeftUp.h"
#include "AttractorStateRightUp.h"
#include "AttractorStateLeftUpDiagonal.h"
#include "AttractorStateRightUpDiagonal.h"

class AttractorMoveFSM
{
private:

public:
	static const AttractorStateLeftDownDiagonal StateLeftDownDiagonal;
	static const AttractorStateRightDownDiagonal StateRightDownDiagonal;
	static const AttractorStateLeftDown StateLeftDown;
	static const AttractorStateRightDown StateRightDown;
	static const AttractorStateLeftUp StateLeftUp;
	static const AttractorStateRightUp StateRightUp;
	static const AttractorStateLeftUpDiagonal StateLeftUpDiagonal;
	static const AttractorStateRightUpDiagonal StateRightUpDiagonal;
};

#endif