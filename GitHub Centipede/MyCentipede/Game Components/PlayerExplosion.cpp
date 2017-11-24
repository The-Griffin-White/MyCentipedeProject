// Explosion
// Andre Berthiaume, March 2013

#include "PlayerExplosion.h"
#include "GameManager.h"

PlayerExplosion::PlayerExplosion()
{
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("PlayerExplosion"), 8, 2, 30.0f); 
	MainSprite.SetAnimation(0, 15); 
	MainSprite.setScale(GameScale, GameScale);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void PlayerExplosion::Initialize(sf::Vector2f p)
{
	MainSprite.SetAnimation(0, 15);
	Pos = p;
	MainSprite.setPosition(Pos);
}

void PlayerExplosion::Update()
{
	if ( MainSprite.IsLastAnimationFrame() )
	{
		GameManager::ResetWave();
		MarkForDestroy();
	}

	MainSprite.Update();
}

void PlayerExplosion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}