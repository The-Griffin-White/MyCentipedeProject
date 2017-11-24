#include "SpiderMovementCollection.h"
#include "Spider.h"
#include "SpiderMoveFSM.h"

#include "SpiderStateLeftDown.h"
#include "SpiderStateLeftDownDiagonal.h"
#include "SpiderStateLeftUp.h"
#include "SpiderStateLeftUpDiagonal.h"
#include "SpiderStateRightDown.h"
#include "SpiderStateRightDownDiagonal.h"
#include "SpiderStateRightUp.h"
#include "SpiderStateRightUpDiagonal.h"

SpiderStateRightUp::SpiderStateRightUp()
{
	pMoveOffsets = &SpiderMovementCollection::OffsetsRightUp;
}
const SpiderState* SpiderStateRightUp::GetNextState(Spider *pSpider) const
{
	const SpiderState* pNextState;

	if (rand() % 2 == 1)
	{
		ConsoleMsg::WriteLine("StateRightDownDiagonal");
		pNextState = &SpiderMoveFSM::StateRightDownDiagonal;
	}
	else
	{
		ConsoleMsg::WriteLine("StateRightDown");
		pNextState = &SpiderMoveFSM::StateRightDown;
	}
	return pNextState;
}