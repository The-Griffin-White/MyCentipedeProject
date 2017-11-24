#include "SpiderMovementCollection.h"
#include "Spider.h"
#include "SpiderMoveFSM.h"

#include "SpiderStateLeftDown.h"
#include "SpiderStateLeftDownDiagonal.h"
#include "SpiderStateLeftUp.h"
#include "SpiderStateLeftUpDiagonal.h"

SpiderStateLeftUpDiagonal::SpiderStateLeftUpDiagonal()
{
	pMoveOffsets = &SpiderMovementCollection::OffsetsLeftUpDiagonal;
}
const SpiderState* SpiderStateLeftUpDiagonal::GetNextState(Spider *pSpider) const
{
	const SpiderState* pNextState;

	if (rand() % 2 == 1)
	{
		ConsoleMsg::WriteLine("StateLeftDownDiagonal");
		pNextState = &SpiderMoveFSM::StateLeftDownDiagonal;
	}
	else
	{
		ConsoleMsg::WriteLine("StateLeftDown");
		pNextState = &SpiderMoveFSM::StateLeftDown;
	}
	return pNextState;
}