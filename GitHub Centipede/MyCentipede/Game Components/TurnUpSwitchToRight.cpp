#include "TurnUpSwitchToRight.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// TurnUpSwitchToRight
const OffsetArray* TurnUpSwitchToRight::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsTurnUpEndRight[i];
}

const MoveState* TurnUpSwitchToRight::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationUpRight[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() + 1; // looking ahead after turn -> Right
		Obstacle obst = chead->Inspect(row, col);

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveRightAndUpwards;
			chead->NextToRight();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row != TopPlayerRow)
			{
				pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
				chead->NextToUp();
			}
			else
			{
				pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
				chead->NextToDown();
			}
		}
		else // poison
		{
			// Idk why this would ever happen
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
		}
		
	//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();

	}
	else
	{
		chead->Iterate();
		pNextState = &MoveFSM::StateTurnUpSwitchToRight;
	}

	return pNextState;
}

const MoveState* TurnUpSwitchToRight::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;

	cbody->Rotate(MovementCollection::RotationUpRight[cbody->GetIterator()]);
	cbody->Iterate();
	pNextState = &MoveFSM::StateTurnUpSwitchToRight;
	return pNextState;
}