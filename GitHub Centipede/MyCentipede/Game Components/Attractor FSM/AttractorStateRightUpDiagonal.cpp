#include "AttractorMovementCollection.h"
#include "AttractorMoveFSM.h"

#include "AttractorStateLeftDown.h"
#include "AttractorStateLeftDownDiagonal.h"
#include "AttractorStateLeftUp.h"
#include "AttractorStateLeftUpDiagonal.h"

#include "AttractorStateRightDown.h"
#include "AttractorStateRightDownDiagonal.h"
#include "AttractorStateRightUp.h"
#include "AttractorStateRightUpDiagonal.h"

#include "../Player/PlayerManager.h"
#include "../Constants.h"

AttractorStateRightUpDiagonal::AttractorStateRightUpDiagonal()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsRightUpDiagonal;
}
const AttractorState* AttractorStateRightUpDiagonal::GetNextState() const
{
	const AttractorState* pNextState;

	sf::Vector2f shipPos = PlayerManager::GetShipPos();

	if (shipPos.y < AttractorMovementCollection::AttractorWindowHeightTop)
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
	else if (shipPos.x > AttractorMovementCollection::AttractorWindowWidthMax)
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
		pNextState = &AttractorMoveFSM::StateRightUpDiagonal;
	}
	return pNextState;
}