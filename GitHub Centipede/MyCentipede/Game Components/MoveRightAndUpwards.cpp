#include "MoveRightAndUpwards.h"

#include "MovementCollection.h"
#include "MushroomField.h"
#include "MoveFSM.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"

// MoveRightAndUpwards
const OffsetArray* MoveRightAndUpwards::GetMoveOffsets(const int i) const
{
	return &MovementCollection::OffsetsStraightRight[i];
}

const MoveState* MoveRightAndUpwards::GetNextHeadState(FSMCentipedeHead* chead) const
{
	const MoveState* pNextState;

	chead->Rotate(MovementCollection::RotationStraightRight[chead->GetIterator()]);

	if (chead->GetIterator() == Centipede_Iterator_Cap)
	{
		chead->UpdateRowAndCol();
//		chead->ColToRight();
		chead->GiveFollowerRowAndColumn();


		int row = chead->GetRow();
		int col = chead->GetColumn() + 1; // looking ahead while right
		Obstacle obst = chead->Inspect(row, col);

		if (obst == Obstacle::Clear)
		{
			pNextState = &MoveFSM::StateMoveRightAndUpwards;
			chead->NextToRight();
		}
		else if (obst == Obstacle::Blocked) // Edge, shroom or letter?
		{
			if (row == TopPlayerRow)
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
			// Idk why this would ever happen
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
		pNextState = &MoveFSM::StateMoveRightAndUpwards;
	}	

	return pNextState;
}

const MoveState* MoveRightAndUpwards::GetNextBodyState(FSMCentipedeBody* cbody) const
{
	const MoveState* pNextState;
	cbody->Iterate();
	pNextState = &MoveFSM::StateMoveRightAndUpwards;
	return pNextState;
}