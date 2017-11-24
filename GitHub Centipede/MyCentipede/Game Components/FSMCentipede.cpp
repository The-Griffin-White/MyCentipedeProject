#include "FSMCentipede.h"

#include "MoveState.h"
#include "MoveFSM.h"
#include "MovementCollection.h"

#include "MushroomField.h"
#include "Direction.h"

#include "FSMCentipedeBody.h"

#include "Player\PlayerManager.h"

FSMCentipede::FSMCentipede()
{
}

FSMCentipede::~FSMCentipede()
{

	ConsoleMsg::WriteLine("calling deletion on centipede");
}

void FSMCentipede::Initialize(int r, int c)
{
}

void FSMCentipede::Rotate(float a)
{
	MainSprite.setRotation(a);
}

sf::Vector2f FSMCentipede::GetPos()
{
	return Pos;
}

void FSMCentipede::NextToRight()
{
	nextCol++;
}
void FSMCentipede::NextToLeft()
{
	nextCol--;
}
void FSMCentipede::NextToUp()
{
	nextRow--;
}
void FSMCentipede::NextToDown()
{
	nextRow++;
}

/// Row and Column offset should be 1 or 0, one each
void FSMCentipede::UpdateRowAndCol()
{
	row = nextRow;
	col = nextCol;
}

void FSMCentipede::SetFollower(FSMCentipedeBody* f)
{
	follower = f;
}

const MoveState* FSMCentipede::GetCommand()
{
	return pCurrentState;
}

void FSMCentipede::SendCommand(const MoveState* c)
{
	if (follower)
	{
		follower->SetCommand(c);
	}
}

void FSMCentipede::SendCommand()
{
	if (follower)
	{
		follower->SetCommand(pCurrentState);
	}
}

void FSMCentipede::TakeRowAndColumn(int r, int c)
{
	int oldRow = this->nextRow;
	int oldCol = this->nextCol;

	this->row = this->nextRow;
	this->col = this->nextCol;

	this->nextRow = r;
	this->nextCol = c;

	if (follower)
		follower->TakeRowAndColumn(oldRow, oldCol);
}

int FSMCentipede::GetIterator()
{
	return itr;
}
void FSMCentipede::Iterate()
{
	itr++;
}
void FSMCentipede::ResetIterator()
{
	itr = 0;
}

void FSMCentipede::Collision(Bullet* other)
{
	if (follower)
	{
		follower->ConvertToHead();
	}
	this->ReportDeath();
	PlayerManager::AddMushroomHere(nextRow, nextCol);
	MarkForDestroy();
}

void FSMCentipede::TestKill()
{
	if (follower)
	{
		follower->ConvertToHead();
	}
	this->ReportDeath();
	PlayerManager::AddMushroomHere(nextRow, nextCol);
	MarkForDestroy();
}