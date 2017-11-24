#include "TurnDownSwitchToRight.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// TurnDownSwitchToRight
const OffsetArray* TurnDownSwitchToRight::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsTurnDownEndRight[i];
}

const MoveState* TurnDownSwitchToRight::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationDownRight[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
//		chead->RowToDown();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() + 1; // looking ahead after turn -> right
		Obstacle obst = chead->Inspect(row, col);

		if (row == BottomRow)
		{
			chead->ReachedBottomRow();
		}

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveRightAndDownwards;
			chead->NextToRight();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row != BottomRow)
			{
				pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
				chead->NextToDown();
			}
			else
			{
				pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
				chead->NextToUp();
			}
		}
		else // poison
		{
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
		}

	//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();

	}
	else
	{
		chead->Iterate();
		pNextState = &MoveFSM::StateTurnDownSwitchToRight;
	}

	return pNextState;
}

const MoveState* TurnDownSwitchToRight::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;

	cbody->Rotate(MovementCollection::RotationDownRight[cbody->GetIterator()]);
	cbody->Iterate();
	pNextState = &MoveFSM::StateTurnDownSwitchToRight;
	return pNextState;
}