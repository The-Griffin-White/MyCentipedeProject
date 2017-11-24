#include "AttractorMovementCollection.h"
#include "AttractorMoveFSM.h"

#include "AttractorStateRightDown.h"
#include "AttractorStateRightDownDiagonal.h"
#include "AttractorStateRightUp.h"
#include "AttractorStateRightUpDiagonal.h"

#include "../Player/PlayerManager.h"
#include "../Constants.h"

AttractorStateRightDown::AttractorStateRightDown()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsRightDown;
}
const AttractorState* AttractorStateRightDown::GetNextState() const
{
	const AttractorState* pNextState;

	if (PlayerManager::GetShipPos().y > AttractorMovementCollection::AttractorWindowHeightBot)
	{
		if (rand() % 2 == 1)
		{
			ConsoleMsg::WriteLine("StateRightUpDiagonal");
			pNextState = &AttractorMoveFSM::StateRightUpDiagonal;
		}
		else
		{
			ConsoleMsg::WriteLine("StateRightUp");
			pNextState = &AttractorMoveFSM::StateRightUp;
		}
	}
	else
	{
		pNextState = &AttractorMoveFSM::StateRightDown;
	}
	return pNextState;
}