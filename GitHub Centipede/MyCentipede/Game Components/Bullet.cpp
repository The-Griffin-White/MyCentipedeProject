// Bullet
// Andre Berthiaume, Aug 2012

#include "Bullet.h"
#include "Ship.h"

	
Bullet::Bullet()
{
	bitmap = ResourceManager::GetTextureBitmap("Bullet");
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Bullet"), 1, 1);
	MainSprite.setScale(GameScale, GameScale);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);

	SetCollider(MainSprite, bitmap);
}

void Bullet::Initialize(sf::Vector2f p, Ship* s)
{
	Pos = p;
	ship = s;
	RegisterCollision<Bullet>(*this);
}

void Bullet::Update()
{
	MainSprite.Update();

	Pos.y -= Bullet_Speed;

	if (Pos.y < MinCellF)
	{
		MarkForDestroy();
	}
	MainSprite.setPosition(Pos);
}

void Bullet::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Bullet::Destroy()
{
	ship = nullptr;
	DeregisterCollision<Bullet>( *this );
}

void Bullet::Collision( Flea *other )
{
	MarkForDestroy();
}

void Bullet::Collision( Scorpion *other)
{
	MarkForDestroy();
}

void Bullet::Collision(Mushroom *other)
{
	MarkForDestroy();
}

void Bullet::Collision( FSMCentipedeHead *other)
{
	MarkForDestroy();
}

void Bullet::Collision( FSMCentipedeBody *other)
{
	MarkForDestroy();
}

sf::Vector2f Bullet::GetShipPos()
{
	return ship->GetPos();
}