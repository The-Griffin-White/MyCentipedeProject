#include "FSMCentipedeBody.h"

#include "MoveState.h"
#include "MoveFSM.h"
#include "MovementCollection.h"
#include "FSMCentipedeFactory.h"

#include "MushroomField.h"
#include "Direction.h"

#include "Player\PlayerManager.h"

FSMCentipedeBody::FSMCentipedeBody()
{
	// Set sprite values
	bitmap = &ResourceManager::GetTextureBitmap("CentipedeBody");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeBody"), 8, 2, 15.0f);
	MainSprite.SetAnimation(0, 7);
	MainSprite.setScale(DoubleScale, DoubleScale);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	
	SetDrawOrder(100);

	SetCollider(MainSprite, *bitmap);
	// ***************************************************
}

void FSMCentipedeBody::Initialize(FSMCentipede* l, int r, int c)
{
	itr = 0;

	row = r;
	col = c;

	Pos = PlayerManager::GetCenterCoordinate(row, col);

	follower = nullptr;

	leader = l;

	if (leader->GetCommand() == &MoveFSM::StateTurnDownSwitchToRight)
	{
		pCurrentState = &MoveFSM::StateTurnDownSwitchToLeft;
	}
	else
	{
		pCurrentState = &MoveFSM::StateTurnDownSwitchToRight;
	}
	nextRow = r + 1;
	nextCol = col;
	pNextState = pCurrentState;

	MainSprite.setPosition(Pos);

	RegisterCollision<FSMCentipedeBody>(*this);
}

void FSMCentipedeBody::Update()
{
	if (itr > Centipede_Iterator_Cap)
	{
//		ConsoleMsg::WriteLine("Somethings broken");
		itr = Centipede_Iterator_Cap;
	}

	Pos.y += pCurrentState->GetMoveOffsets(itr)->rowoffset;
	Pos.x += pCurrentState->GetMoveOffsets(itr)->coloffset;

	pCurrentState = pNextState->GetNextBodyState(this);

	MainSprite.setPosition(Pos);
	MainSprite.Update();
}

void FSMCentipedeBody::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void FSMCentipedeBody::Destroy()
{
	follower = nullptr;
	leader->SetFollower(nullptr);
	leader = nullptr;
	DeregisterCollision<FSMCentipedeBody>(*this);
}

void FSMCentipedeBody::SetLeader(FSMCentipede* l)
{
	leader = l;
}

void FSMCentipedeBody::SetCommand(const MoveState* c)
{
	pNextState = c;
	ResetIterator();
	SendCommand();
}

void FSMCentipedeBody::ConvertToHead()
{
	FSMCentipedeFactory::ConvertBodyToHead(Pos, row, nextRow, col, nextCol, pNextState, follower, itr);
	MarkForDestroy();
}

// Get all the info we need to create a new head to replace this body
sf::Vector2f FSMCentipedeBody::GetPos()
{
	return Pos;
}
int FSMCentipedeBody::GetRow()
{
	return row;
}
int FSMCentipedeBody::GetNextRow()
{
	return nextRow;
}
int FSMCentipedeBody::GetCol()
{
	return col;
}
int FSMCentipedeBody::GetNextCol()
{
	return nextCol;
}
const MoveState* FSMCentipedeBody::GetCurrentState()
{
	return pCurrentState;
}
FSMCentipedeBody* FSMCentipedeBody::GetFollower()
{
	return follower;
}

void FSMCentipedeBody::ReportDeath()
{
	FSMCentipedeFactory::ReportBodyDeath();
}