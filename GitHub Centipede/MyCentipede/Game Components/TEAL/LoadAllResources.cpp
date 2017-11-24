// LoadAllResources.cpp
// Andre Berthiaume, June 2012
//
// The user fills the method with all resources that need loading

#include "ResourceManager.h"
#include "../Level1.h"

void ResourceManager::LoadAllResources()
{
	SetStartScene( new Level1 );

	AddTexture("Blaster", "blaster.png");
	AddTexture("Bullet", "bullet.png");
	AddTexture("Mushroom", "mushroom.png");
	AddTexture("PlayerExplosion", "death.png");
	AddTexture("EnemyExplosion", "spawn.png");
	AddTexture("Flea", "flea.png");
	AddTexture("Scorpion", "scorpion.png");
	AddTexture("CentipedeHead", "centipede_head.png");
	AddTexture("CentipedeBody", "centipede_segment.png");
	AddTexture("Spider", "spider.png");
	AddTexture("SpiderScore", "SpiderScore.png");

	AddSound("Fire", "fire1.wav");
	AddSound("PlayerDeath", "death.wav");
	AddSound("Kill", "kill.wav");
	AddSound("Flea", "flea_new.wav");
	AddSound("Scorpion", "scorpion_new.wav");
	AddSound("Centipede", "beat.wav");
	AddSound("Spider", "spider_new.wav");
	AddSound("MushroomBonus", "bonus.wav");

	AddTexture("Alphabet", "FONTwPLAYER.bmp");
	AddFont("PointFont", "MotorwerkOblique.ttf" );
}

