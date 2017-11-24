#include "PoisonTurnDownSwitchToLeft.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// PoisonTurnDownSwitchToLeft
const OffsetArray* PoisonTurnDownSwitchToLeft::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsPoisonTurnDownEndLeft[i];
}

const MoveState* PoisonTurnDownSwitchToLeft::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationDownLeft[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
//		chead->RowToDown();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() - 1; // looking ahead after turn ->left

		// Keep going until we reach the bottom row
		if (row < MaxCell)
		{
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
			chead->NextToDown();
		}
		else
		{
			Obstacle obst = chead->Inspect(row, col);
			chead->ReachedBottomRow();

			if (obst == Obstacle::Clear)
			{
				pNextState = &MoveFSM::StateMoveLeftAndUpwards;
				chead->NextToLeft();
			}

			else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
			{
				pNextState = &MoveFSM::StateTurnUpSwitchToRight;
				chead->NextToUp();
			}

			else // poison
			{
				// Idk why this would ever happen
				pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
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
		pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
	}
	

	return pNextState;
}

const MoveState* PoisonTurnDownSwitchToLeft::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;

	cbody->Rotate(MovementCollection::RotationDownLeft[cbody->GetIterator()]);
	cbody->Iterate();
	pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
	return pNextState;
}