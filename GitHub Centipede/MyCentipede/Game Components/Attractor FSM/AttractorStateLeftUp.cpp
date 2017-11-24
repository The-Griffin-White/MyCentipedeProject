#include "AttractorMovementCollection.h"
#include "AttractorMoveFSM.h"

#include "AttractorStateLeftDown.h"
#include "AttractorStateLeftDownDiagonal.h"
#include "AttractorStateLeftUp.h"
#include "AttractorStateLeftUpDiagonal.h"

#include "../Player/PlayerManager.h"
#include "../Constants.h"

AttractorStateLeftUp::AttractorStateLeftUp()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsLeftUp;
}
const AttractorState* AttractorStateLeftUp::GetNextState() const
{
	const AttractorState* pNextState;

	if (PlayerManager::GetShipPos().y < AttractorMovementCollection::AttractorWindowHeightTop)
	{
		if (rand() % 2 == 1)
		{
			ConsoleMsg::WriteLine("StateLeftDownDiagonal");
			pNextState = &AttractorMoveFSM::StateLeftDownDiagonal;
		}
		else
		{
			ConsoleMsg::WriteLine("StateLeftDown");
			pNextState = &AttractorMoveFSM::StateLeftDown;
		}
	}
	else
	{
		pNextState = &AttractorMoveFSM::StateLeftUp;
	}
	return pNextState;
}