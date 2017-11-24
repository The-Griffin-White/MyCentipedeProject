#include "SpiderMovementCollection.h"
#include "Spider.h"
#include "SpiderMoveFSM.h"

#include "SpiderStateLeftDown.h"
#include "SpiderStateLeftDownDiagonal.h"
#include "SpiderStateLeftUp.h"
#include "SpiderStateLeftUpDiagonal.h"

SpiderStateLeftDown::SpiderStateLeftDown()
{
	pMoveOffsets = &SpiderMovementCollection::OffsetsLeftDown;
}
const SpiderState* SpiderStateLeftDown::GetNextState(Spider *pSpider) const
{
	const SpiderState* pNextState;

	if (rand() % 2 == 1)
	{
		ConsoleMsg::WriteLine("StateLeftUpDiagonal");
		pNextState = &SpiderMoveFSM::StateLeftUpDiagonal;
	}
	else
	{
		ConsoleMsg::WriteLine("StateLeftUp");
		pNextState = &SpiderMoveFSM::StateLeftUp;
	}
	return pNextState;
}