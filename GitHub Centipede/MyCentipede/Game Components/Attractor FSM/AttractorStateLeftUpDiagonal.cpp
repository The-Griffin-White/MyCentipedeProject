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

AttractorStateLeftUpDiagonal::AttractorStateLeftUpDiagonal()
{
	pMoveOffsets = &AttractorMovementCollection::OffsetsLeftUpDiagonal;
}
const AttractorState* AttractorStateLeftUpDiagonal::GetNextState() const
{
	const AttractorState* pNextState;

	sf::Vector2f shipPos = PlayerManager::GetShipPos();

	if (shipPos.y < AttractorMovementCollection::AttractorWindowHeightTop)
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
	else if (shipPos.x < AttractorMovementCollection::AttractorWindowWidthMin)
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
		pNextState = &AttractorMoveFSM::StateLeftUpDiagonal;
	}
	return pNextState;
}