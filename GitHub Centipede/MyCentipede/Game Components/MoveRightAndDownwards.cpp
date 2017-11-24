#include "MoveRightAndDownwards.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// MoveRightAndDownwards
const OffsetArray* MoveRightAndDownwards::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsStraightRight[i];
}

const MoveState* MoveRightAndDownwards::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationStraightRight[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() + 1; // looking ahead while right
		Obstacle obst = chead->Inspect(row, col);

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveRightAndDownwards;
			chead->NextToRight();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row == BottomRow)
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
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToLeft;
			chead->NextToDown();
		}

		//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();

	}
	else
	{
		chead->Iterate();
		pNextState = &MoveFSM::StateMoveRightAndDownwards;
	}

	return pNextState;
}

const MoveState* MoveRightAndDownwards::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;
	cbody->Iterate();
	pNextState = &MoveFSM::StateMoveRightAndDownwards;
	return pNextState;
}