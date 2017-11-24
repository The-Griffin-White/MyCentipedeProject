#include "AttractorMovementCollection.h"
#include "AttractorMoveFSM.h"

#include "AttractorStateRightDown.h"
#include "AttractorStateRightDownDiagonal.h"
#include "AttractorStateRightUp.h"
#include "AttractorStateRightUpDiagonal.h"

#include "../Player/PlayerManager.h"
#include "../Constants.h"

AttractorStateRightUp::AttractorStateRightUp()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsRightUp;
}
const AttractorState* AttractorStateRightUp::GetNextState() const
{
	const AttractorState* pNextState;

	if (PlayerManager::GetShipPos().y < AttractorMovementCollection::AttractorWindowHeightTop)
	{
		if (rand() % 2 == 1)
		{
			ConsoleMsg::WriteLine("StateRightDownDiagonal");
			pNextState = &AttractorMoveFSM::StateRightDownDiagonal;
		}
		else
		{
			ConsoleMsg::WriteLine("StateRightDown");
			pNextState = &AttractorMoveFSM::StateRightDown;
		}
	}
	else
	{
		pNextState = &AttractorMoveFSM::StateRightUp;
	}
	return pNextState;
}