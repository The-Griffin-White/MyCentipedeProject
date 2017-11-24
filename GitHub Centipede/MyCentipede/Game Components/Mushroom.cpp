#include "Mushroom.h"
#include "Bullet.h"
#include "MushroomField.h"
#include "MushroomFactory.h"

Mushroom::Mushroom()
{
	bitmap = &ResourceManager::GetTextureBitmap("Mushroom");
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Mushroom"), 4, 2);
	
	MainSprite.scale(GameScale, GameScale);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);


	MAXHEALTH = Mushroom_MaxHealth;

	SetCollider(MainSprite, *bitmap);
}

void Mushroom::Initialize(sf::Vector2f p, MushroomField* g, int i, int j)
{
	Pos = p;
	grid = g;
	x = i;
	y = j;

	MainSprite.setPosition(Pos);

	health = MAXHEALTH;
	spriteValue = 0;
	ChangeMushroomSprite();

	RegisterCollision<Mushroom>(*this);
}

void Mushroom::Update()
{
	MainSprite.Update();
}

void Mushroom::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}

void Mushroom::Collision( Bullet *other )
{
	health -= Mushroom_Damage_From_Bullet;

	if (health <= 0)
	{
		MushroomFactory::ReportMushroomDeath();

		RemoveFromGrid();

		MarkForDestroy();
	}
	else
	{
		ChangeMushroomSprite();
	}
}

void Mushroom::MushroomEaten()
{
	RemoveFromGrid();

	MarkForDestroy();
}

void Mushroom::RemoveFromGrid()
{
	if (grid)
		grid->DeleteMushroom(x, y);
	grid = nullptr;
}

bool Mushroom::IsMushroomHurt()
{
	if (health < MAXHEALTH)
		return true;
	else
		return false;
}

void Mushroom::Heal(int amount)
{
	health += amount;
	if (health > MAXHEALTH)
		health = MAXHEALTH;
	MakeNonPoison();
}

void Mushroom::Destroy()
{
	grid = nullptr;
	DeregisterCollision<Mushroom>( *this );
}

sf::Vector2f Mushroom::GetPos()
{
	return Pos;
}

void Mushroom::MakePoison()
{
	spriteValue = 4;
	ChangeMushroomSprite();
}

void Mushroom::MakeNonPoison()
{
	spriteValue = 0;
	ChangeMushroomSprite();
	grid->MakeMushroomNonPoison(x, y);
}

void Mushroom::ChangeMushroomSprite()
{
	MainSprite.SetAnimation(MAXHEALTH - health + spriteValue, MAXHEALTH - health + spriteValue, false);
}