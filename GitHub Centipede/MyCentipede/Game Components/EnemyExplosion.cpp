#include "EnemyExplosion.h"

EnemyExplosion::EnemyExplosion()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("EnemyExplosion"), 3, 2, 30.0f);
	MainSprite.SetAnimation(0, 5);
	MainSprite.setScale(DoubleScale, DoubleScale);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void EnemyExplosion::Initialize(sf::Vector2f p)
{
	MainSprite.SetAnimation(0, 5);
	Pos = p;
	MainSprite.setPosition(Pos);
}

void EnemyExplosion::Update()
{
	if (MainSprite.IsLastAnimationFrame())
		MarkForDestroy();

	MainSprite.Update();
}

void EnemyExplosion::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}