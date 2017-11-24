#include "MoveLeftAndDownwards.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// MoveLeftAndDownwards
const OffsetArray* MoveLeftAndDownwards::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsStraightLeft[i];
}

const MoveState* MoveLeftAndDownwards::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationStraightLeft[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
		chead->GiveFollowerRowAndColumn();

		int row = chead->GetRow();
		int col = chead->GetColumn() - 1; // looking ahead while left
		Obstacle obst = chead->Inspect(row, col);

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveLeftAndDownwards;
			chead->NextToLeft();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row == BottomRow)
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
			pNextState = &MoveFSM::StatePoisonTurnDownSwitchToRight;
			chead->NextToDown();
		}

		//	chead->SendCommand(pNextState);
		chead->SendCommand();
		chead->ResetIterator();

	}
	else
	{
		chead->Iterate(); 
		pNextState = &MoveFSM::StateMoveLeftAndDownwards;
	}
	return pNextState;
}

const MoveState* MoveLeftAndDownwards::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;
	cbody->Iterate();
	pNextState = &MoveFSM::StateMoveLeftAndDownwards;

	return pNextState;
}