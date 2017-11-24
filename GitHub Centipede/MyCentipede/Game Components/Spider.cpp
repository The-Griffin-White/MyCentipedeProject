#include "Spider.h"
#include "Bullet.h"
#include "Direction.h"
#include "EnemyExplosionFactory.h"
#include "SpiderFactory.h"

#include "SpiderState.h"
#include "SpiderMoveFSM.h"
#include "SpiderMovementCollection.h"
#include "SpiderStateLeftUpDiagonal.h"
#include "SpiderStateRightUpDiagonal.h"

#include "Player\PlayerManager.h"

Spider::Spider()
{
//	ConsoleMsg::WriteLine("Spawning Spider");

	bitmap = &ResourceManager::GetTextureBitmap("Spider");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Spider"), 4, 2, 30.0f);
	MainSprite.SetAnimation(0, 7);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f - CellSize_Half, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.scale(DoubleScale, DoubleScale);

	SetCollider(MainSprite, *bitmap);
	
}

void Spider::Initialize(Direction d)
{
	itr = 0;
	cellItr = 0;

	if (d == Left)
	{
		row = MaxCell;
		col = MaxCell + 2;
		Pos = PlayerManager::GetCenterCoordinate(row, col - 1);
		pCurrentState = &SpiderMoveFSM::StateLeftUpDiagonal;
	}
	else
	{
		row = MaxCell;
		col = MinCell;
		Pos = PlayerManager::GetCenterCoordinate(row, col - 1);
		pCurrentState = &SpiderMoveFSM::StateRightUpDiagonal;
	}

	RegisterCollision<Spider>(*this);

}

void Spider::Update()
{
	Pos.y += pCurrentState->GetMoveOffsets()->rowoffset;
	Pos.x += pCurrentState->GetMoveOffsets()->coloffset;

	itr++;
	cellItr++;
	if (cellItr == Spider_Iterator_Cap)
	{
		row += pCurrentState->NextRow();
		col += pCurrentState->NextCol();
		cellItr = 0;
		if ((col >= MinCell && col <= MaxCell && row <= MaxCell) && PlayerManager::InspectCentipedeObstacles(row, col) != Obstacle::Clear)
		{
			PlayerManager::EatMushroom(row, col);
		}
		if (itr == Spider_Field_Iterator_Cap)
		{
			pCurrentState = pCurrentState->GetNextState(this);
			itr = 0;
		}
	}
	MainSprite.Update();
	MainSprite.setPosition(Pos);

	if (Pos.x < 0 - CellSize * 2 || Pos.x > GameWindowWidth + CellSize * 2)
	{
		MarkForDestroy();
	}
}

sf::Vector2f Spider::GetPos()
{
	return Pos;
}
float Spider::GetY()
{
	return Pos.y;
}
float Spider::GetX()
{
	return Pos.x;
}

void Spider::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Spider::Collision(Bullet *other)
{
	EnemyExplosionFactory::CreateEnemyExplosion(Pos);
	SpiderFactory::ReportSpiderDeath(Pos, other->GetShipPos());
	MarkForDestroy();
}

void Spider::Destroy()
{
	ConsoleMsg::WriteLine("Destroying Spider");
	DeregisterCollision<Spider>(*this);
}