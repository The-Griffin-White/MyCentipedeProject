#include "TurnDownSwitchToLeft.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// TurnDownSwitchToLeft
const OffsetArray* TurnDownSwitchToLeft::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsTurnDownEndLeft[i];
}

const MoveState* TurnDownSwitchToLeft::GetNextHeadState(FSMCentipedeHead* chead) const
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
		Obstacle obst = chead->Inspect(row, col);

		if (row == BottomRow)
		{
			chead->ReachedBottomRow();
		}

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveLeftAndDownwards;
			chead->NextToLeft();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row != BottomRow)
			{
				pNextState = &MoveFSM::StateTurnDownSwitchToRight;
				chead->NextToDown();
			}
			else
			{
				pNextState = &MoveFSM::StateTurnUpSwitchToRight;
				chead->NextToUp();
			}
		}
		else // poison
		{
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
		}

		//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();

	}
	else
	{
		chead->Iterate();
		pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
	}

	return pNextState;
}

const MoveState* TurnDownSwitchToLeft::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;

	cbody->Rotate(MovementCollection::RotationDownLeft[cbody->GetIterator()]);
	cbody->Iterate();
	pNextState = &MoveFSM::StateTurnDownSwitchToLeft;

	return pNextState;
}