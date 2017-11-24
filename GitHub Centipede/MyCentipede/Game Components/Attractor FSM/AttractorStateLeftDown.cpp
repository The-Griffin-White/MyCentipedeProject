#include "AttractorMovementCollection.h"
#include "AttractorMoveFSM.h"

#include "AttractorStateLeftDown.h"
#include "AttractorStateLeftDownDiagonal.h"
#include "AttractorStateLeftUp.h"
#include "AttractorStateLeftUpDiagonal.h"

#include "../Player/PlayerManager.h"
#include "../Constants.h"

AttractorStateLeftDown::AttractorStateLeftDown()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsLeftDown;
}
const AttractorState* AttractorStateLeftDown::GetNextState() const
{
	const AttractorState* pNextState;

	if (PlayerManager::GetShipPos().y > AttractorMovementCollection::AttractorWindowHeightBot)
	{
		if (rand() % 2 == 1)
		{
			ConsoleMsg::WriteLine("StateLeftUpDiagonal");
			pNextState = &AttractorMoveFSM::StateLeftUpDiagonal;
		}
		else
		{
			ConsoleMsg::WriteLine("StateLeftUp");
			pNextState = &AttractorMoveFSM::StateLeftUp;
		}
	}
	else
	{
		pNextState = &AttractorMoveFSM::StateLeftDown;
	}
	return pNextState;
}