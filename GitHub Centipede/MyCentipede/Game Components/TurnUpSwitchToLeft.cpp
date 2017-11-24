#include "TurnUpSwitchToLeft.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// TurnUpSwitchToLeft
const OffsetArray* TurnUpSwitchToLeft::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsTurnUpEndLeft[i];
}

const MoveState* TurnUpSwitchToLeft::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationUpLeft[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() - 1; // looking ahead after turn -> left
		Obstacle obst = chead->Inspect(row, col);

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveLeftAndUpwards;
			chead->NextToLeft();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row != TopPlayerRow)
			{
				pNextState = &MoveFSM::StateTurnUpSwitchToRight;
				chead->NextToUp();
			}
			else
			{
				pNextState = &MoveFSM::StateTurnDownSwitchToRight;
				chead->NextToDown();
			}
		}
		else // poison
		{
			// Idk why this would ever happen
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
		}

	//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();

	}
	else
	{
		chead->Iterate();
		pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
	}

	return pNextState;
}

const MoveState* TurnUpSwitchToLeft::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;

	cbody->Rotate(MovementCollection::RotationUpLeft[cbody->GetIterator()]);
	cbody->Iterate();
	pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
	return pNextState;
}