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

AttractorStateLeftDownDiagonal::AttractorStateLeftDownDiagonal()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsLeftDownDiagonal;
}
const AttractorState* AttractorStateLeftDownDiagonal::GetNextState() const
{
	const AttractorState* pNextState;

	sf::Vector2f shipPos = PlayerManager::GetShipPos();

	if (shipPos.y > AttractorMovementCollection::AttractorWindowHeightBot)
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
	else if (shipPos.x < AttractorMovementCollection::AttractorWindowWidthMin)
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
		pNextState = &AttractorMoveFSM::StateLeftDownDiagonal;
	}
	return pNextState;
}