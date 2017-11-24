#include "MoveLeftAndUpwards.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// MoveLeftAndUpwards
const OffsetArray* MoveLeftAndUpwards::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsStraightLeft[i];
}

const MoveState* MoveLeftAndUpwards::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationStraightLeft[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
//		chead->ColToLeft();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() - 1; // looking ahead while left
		Obstacle obst = chead->Inspect(row, col);

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveLeftAndUpwards;
			chead->NextToLeft();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row == TopPlayerRow)
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
			// idk why this would ever happen
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
		pNextState = &MoveFSM::StateMoveLeftAndUpwards;
	}

	return pNextState;
}

const MoveState* MoveLeftAndUpwards::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;
	cbody->Iterate();
	pNextState = &MoveFSM::StateMoveLeftAndUpwards;

	return pNextState;
}