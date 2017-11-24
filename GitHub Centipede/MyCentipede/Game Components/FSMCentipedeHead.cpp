#include "FSMCentipedeHead.h"

#include "FSMCentipedeBody.h"
#include "FSMCentipedeFactory.h"

#include "MoveState.h"
#include "MoveFSM.h"
#include "MovementCollection.h"

#include "MushroomField.h"
#include "Direction.h"

#include "Player\PlayerManager.h"

FSMCentipedeHead::FSMCentipedeHead()
{
	// Set sprite values
	bitmap = &ResourceManager::GetTextureBitmap("CentipedeHead");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeHead"), 8, 2, 15.0f);
	MainSprite.SetAnimation(0, 7);
	MainSprite.setScale(DoubleScale, DoubleScale);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);

	SetDrawOrder(100);

	SetCollider(MainSprite, *bitmap);
	// ***************************************************

}

void FSMCentipedeHead::Initialize(int r, int c, Direction lr, Direction ud)
{
	itr = 0;

	row = r;
	col = c;

	Pos = PlayerManager::GetCenterCoordinate(row, col);

	follower = nullptr;

	if (lr == Right && ud == Down)
	{
		pCurrentState = &MoveFSM::StateTurnDownSwitchToRight;
		nextRow = r + 1;
	}
	else if (lr == Right && ud == Up)
	{
		pCurrentState = &MoveFSM::StateTurnUpSwitchToRight;
		nextRow = r - 1;
	}
	else if (lr == Left && ud == Up)
	{
		pCurrentState = &MoveFSM::StateTurnUpSwitchToLeft;
		nextRow = r - 1;
	}
	else
	{
		pCurrentState = &MoveFSM::StateTurnDownSwitchToLeft;
		nextRow = r + 1;
	}
	nextCol = col;

	MainSprite.setPosition(Pos);

	RegisterCollision<FSMCentipedeHead>(*this);
}


void FSMCentipedeHead::Initialize(sf::Vector2f p, int r, int nr, int c, int nc, const MoveState* s, FSMCentipedeBody* f, int i)
{
	itr = i;

	row = r;
	nextRow = nr;
	col = c;
	nextCol = nc;

	Pos = p;

	follower = f;

	pCurrentState = s;

	MainSprite.setPosition(Pos);

	RegisterCollision<FSMCentipedeHead>(*this);
}

void FSMCentipedeHead::Update()
{
	Pos.y += pCurrentState->GetMoveOffsets(itr)->rowoffset;
	Pos.x += pCurrentState->GetMoveOffsets(itr)->coloffset;

	if (itr > Centipede_Iterator_Cap)
	{
//		ConsoleMsg::WriteLine("Somethings broken");
		itr = Centipede_Iterator_Cap;
	}

	pCurrentState = pCurrentState->GetNextHeadState(this);

	MainSprite.setPosition(Pos);
	MainSprite.Update();
}
void FSMCentipedeHead::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}
void FSMCentipedeHead::Destroy()
{
	follower = nullptr;
	DeregisterCollision<FSMCentipedeHead>(*this);
}

Obstacle FSMCentipedeHead::Inspect(int r, int c)
{
	return PlayerManager::InspectCentipedeObstacles(r, c);
}

int FSMCentipedeHead::GetRow()
{
	return row;
}
int FSMCentipedeHead::GetColumn()
{
	return col;
}

void FSMCentipedeHead::GiveFollowerRowAndColumn()
{
	if (follower)
		follower->TakeRowAndColumn(row, col);
}

void FSMCentipedeHead::ReachedBottomRow()
{
	FSMCentipedeFactory::CreateSoloHeadFromPlayerArea();
}

void FSMCentipedeHead::ReportDeath()
{
	FSMCentipedeFactory::ReportHeadDeath();
}