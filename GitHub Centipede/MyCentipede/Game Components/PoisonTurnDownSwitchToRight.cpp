#include "PoisonTurnDownSwitchToRight.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// PoisonTurnDownSwitchToRight
const OffsetArray* PoisonTurnDownSwitchToRight::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsPoisonTurnDownEndRight[i];
}

const MoveState* PoisonTurnDownSwitchToRight::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationDownRight[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
//		chead->RowToDown();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() + 1; // looking ahead after turn ->left

		// Keep going until we reach the bottom row
		if (row < MaxCell)
		{
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
			chead->NextToDown();
		}
		else
		{
			Obstacle obst = chead->Inspect(row, col);
			chead->ReachedBottomRow();

			if (obst == Obstacle::Clear)
			{
				pNextState = &MoveFSM::StateMoveRightAndUpwards;
				chead->NextToRight();
			}

			else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
			{
				pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
				chead->NextToUp();
			}

			else // poison
			{
				// Idk why this would ever happen
				pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
				chead->NextToDown();
			}
		}

		//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();
	}
	else
	{
		chead->Iterate();
		pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
	}

	return pNextState;
}

const MoveState* PoisonTurnDownSwitchToRight::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;

	cbody->Rotate(MovementCollection::RotationDownRight[cbody->GetIterator()]);
	cbody->Iterate();
	pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
	return pNextState;
}