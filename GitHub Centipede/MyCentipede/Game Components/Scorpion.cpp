#include "Scorpion.h"
#include "ScorpionFactory.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "EnemyExplosionFactory.h"

#include "Player\PlayerManager.h"

#include "ScorpionRightStrategy.h"
#include "ScorpionLeftStrategy.h"

#include "GridSpace.h"

Scorpion::Scorpion()
{
	bitmap = &ResourceManager::GetTextureBitmap("Scorpion");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Scorpion"), 4, 1, 10.0f, 0, 3, true, true);
	MainSprite.SetAnimation(0, 3);
	MainSprite.setScale(GameScale, DoubleScale);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);

	SetCollider(MainSprite, *bitmap);

	left = new ScorpionLeftStrategy;
	right = new ScorpionRightStrategy;
}

void Scorpion::Initialize(int r, Direction d)
{
	itr = 0;
	row = r;
	if (d == Right)
	{
		col = -1;
		Pos = PlayerManager::GetCenterCoordinate(row, col);
		move = right;
		MainSprite.setScale(-1 * GameScale, GameScale);
	}
	else
	{
		col = FieldDimensions + 1;
		Pos = PlayerManager::GetCenterCoordinate(row, col);
		move = left;
		MainSprite.setScale(GameScale, GameScale);
	}

	RegisterCollision<Scorpion>(*this);
}

void Scorpion::Update()
{
	MainSprite.Update();

	itr++;
	if (itr == Scorpion_Iterator_Cap)
	{
		col += move->NextCol();
		if (PlayerManager::InspectCentipedeObstacles(row, col) == Obstacle::Blocked)
		{
			PlayerManager::MakeMushroomPoison(row, col);
		}
		itr = 0;
	}
	Pos.x += move->GetMovement();

	MainSprite.setPosition(Pos);
	if (Pos.x > GameWindowWidth + CellSize * 2 || Pos.x < 0 - CellSize * 2)
	{
		MarkForDestroy();
	}
}
void Scorpion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}
void Scorpion::Destroy()
{
	DeregisterCollision<Scorpion>(*this);
}

void Scorpion::Collision(Bullet *other)
{
	EnemyExplosionFactory::CreateEnemyExplosion(Pos);
	ScorpionFactory::ReportScorpionDeath();
	MarkForDestroy();
}