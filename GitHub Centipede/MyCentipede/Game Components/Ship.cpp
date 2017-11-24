// Ship

#include "Ship.h"
#include "BulletFactory.h"
#include "Mushroom.h"
#include "PlayerExplosionFactory.h"
#include "Controller.h"

#include "Player\PlayerManager.h"
#include "PlayerMushroomCollision.h"

Ship::Ship()
{
	bitmap = ResourceManager::GetTextureBitmap("Blaster"); 
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Blaster"), 1, 1);	

	MainSprite.setOrigin( MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.scale(GameScale, GameScale);

	SetCollider(MainSprite, bitmap, true);
	
	SetDrawOrder(ShipDrawOrder);

	collider = new PlayerMushroomCollision;
}

void Ship::Initialize()
{
	Pos = PlayerManager::GetCenterCoordinate(Ship_Start_Row, Ship_Start_Col);
	MainSprite.setPosition(Pos);
	PrevPos = Pos;

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
	RegisterCollision<Ship>(*this);

}

Ship::~Ship()
{
	delete collider;
}

void Ship::Destroy()
{
	DeregisterInput();
	DeregisterCollision<Ship>(*this);
}

void Ship::Update()
{
	MainSprite.Update();
	PrevPos = Pos;

	Pos += PlayerManager::GetPlayerDirections();
	PlayerManager::GetPlayerFireCommand();

	Tools::Clamp<float>(Pos.x, PlayerSpaceLeft, PlayerSpaceRight);
	Tools::Clamp<float>(Pos.y, PlayerSpaceHeight, PlayerSpaceBottom);
	MainSprite.setPosition(Pos);
}

void Ship::ShootBullet()
{
	BulletFactory::CreateBullet(Pos, this);
}

void Ship::LastPos()
{
	// Placeholder. Ideally collision should be handled using the mushroom grid to clamp based on where the ship is lined up, 
	// no use of the actual collision methods
	Pos = PrevPos;
}

void Ship::Collision(Mushroom *other)
{
	collider->Collide(this);
}

void Ship::Collision(FSMCentipedeHead *other)
{
	PlayerExplosionFactory::CreatePlayerExplosion(Pos);
	MarkForDestroy();
}

void Ship::Collision(FSMCentipedeBody *other)
{
	PlayerExplosionFactory::CreatePlayerExplosion(Pos);
	MarkForDestroy();
}

void Ship::Collision(Spider *other)
{
	PlayerExplosionFactory::CreatePlayerExplosion(Pos);
	MarkForDestroy();
}

void Ship::Collision(Flea *other)
{
	PlayerExplosionFactory::CreatePlayerExplosion(Pos);
	MarkForDestroy();
}

void Ship::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

sf::Vector2f Ship::GetPos()
{
	return Pos;
}