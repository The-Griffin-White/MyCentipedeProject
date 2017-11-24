#include "Flea.h"
#include "Bullet.h"
#include "MushroomField.h"
#include "EnemyExplosionFactory.h"

#include "FleaFactory.h"

#include "Player\PlayerManager.h"

#include "FleaOutOfBounds.h"
#include "FleaBase.h"
#include "FleaHurt.h"

static const FleaOutOfBounds Inactive;
static const FleaHurt HurtSpeed;
static const FleaBase BaseSpeed;

Flea::Flea()
{
	bitmap = &ResourceManager::GetTextureBitmap("Flea");
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Flea"), 2, 2);
	MainSprite.SetAnimation(0, 3);

	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f - CellSize_Half, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.scale(GameScale, GameScale);

	// Just making sure the sprite lays on top of any spawned mushrooms
	SetDrawOrder(1000);

	SetCollider(MainSprite, *bitmap);

	MAXHEALTH = Flea_MaxHealth;
}

Flea::~Flea()
{
	pCurrMovement = nullptr;
}

void Flea::Initialize(int c)
{
	pCurrMovement = &Inactive;

	row = -2;			// A little bit above the screen
	col = c;
	Pos = PlayerManager::GetCenterCoordinate(row, col);

	health = MAXHEALTH;

	itr = 0;

	RegisterCollision<Flea>(*this);
}

void Flea::Update()
{
	MainSprite.Update();

	Pos.y += pCurrMovement->Move(this).y;

	if (Pos.y > GameWindowHeight)
		MarkForDestroy();

	MainSprite.setPosition(Pos);
}
void Flea::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

int Flea::GetRow()
{
	return row;
}

void Flea::Collision(Bullet *other)
{
//	ConsoleMsg::WriteLine("Flea hit a bullet");
	health -= Flea_Damage_From_Bullet;
	pCurrMovement->FleaHit(this);
}

void Flea::Destroy()
{
	DeregisterCollision<Flea>(*this);
}

void Flea::DropMushrooms()
{
	PlayerManager::AddMushroomHere(row, col);
}

void Flea::NextRow()
{
	row++;
}

void Flea::ActivateFlea()
{
	pCurrMovement = &BaseSpeed;
}

void Flea::DeactivateFlea()
{
	pCurrMovement = &Inactive;
}

void Flea::SetFleaHurt()
{
	pCurrMovement = &HurtSpeed;
}

void Flea::KillFlea()
{
	EnemyExplosionFactory::CreateEnemyExplosion(Pos);
	FleaFactory::ReportFleaDeath();
	MarkForDestroy();
}

int Flea::GetIterator()
{
	return itr;
}

void Flea::Iterate()
{
	itr++;
}

void Flea::ResetIterator()
{
	itr = 0;
}