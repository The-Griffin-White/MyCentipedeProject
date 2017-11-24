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

SpiderStateRightDown::SpiderStateRightDown()
{
	pMoveOffsets = &SpiderMovementCollection::OffsetsRightDown;
}
const SpiderState* SpiderStateRightDown::GetNextState(Spider *pSpider) const
{
	const SpiderState* pNextState;

	if (rand() % 2 == 1)
	{
		ConsoleMsg::WriteLine("StateRightUpDiagonal");
		pNextState = &SpiderMoveFSM::StateRightUpDiagonal;
	}
	else
	{
		ConsoleMsg::WriteLine("StateRightUp");
		pNextState = &SpiderMoveFSM::StateRightUp;
	}
	return pNextState;
}