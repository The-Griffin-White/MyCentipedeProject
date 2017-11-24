// CentipedeLevel
// Andre Berthiaume, MArch 2013

#include "TEAL\CommonElements.h"

#include "Level1.h"
#include "MushroomField.h"
#include "Controller.h"
#include "PlayerController.h"
#include "AttractorController.h"

#include "Ship.h"
#include "Spider.h"
#include "Bullet.h"
#include "Scorpion.h"
#include "Flea.h"
#include "Mushroom.h"

#include "FSMCentipedeBody.h"
#include "FSMCentipedeHead.h"

#include "GameManager.h"
#include "Player\PlayerManager.h"
#include "Player\Player.h"

#include "Player\PlayerOneHUDStrategy.h"
#include "Player\AttractorHUDStrategy.h"

#include "MushroomFactory.h"
#include "FSMCentipedeFactory.h"
#include "SpiderFactory.h"
#include "FleaFactory.h"
#include "ScorpionFactory.h"
#include "EnemyExplosionFactory.h"
#include "ShipFactory.h"
#include "BulletFactory.h"
#include "PlayerExplosionFactory.h"

#include "SpiderScoreFactory.h"
#include "SpawnerFactory.h"
#include "MushroomRegeneratorFactory.h"
#include "WaveFactory.h"
#include "HUD\GlyphFactory.h"

#include "Audio Manager\AudioManager.h"
#include "ScoreManager.h"
#include "HUD\HUDManager.h"

void Level1::Initialize()
{
	WindowManager::SetBackgroundColor( sf::Color(0,0,0,255) );

	PlayerManager::Initialize(new Player(new PlayerController, new MushroomField, new PlayerOneHUDStrategy),
							new Player(new AttractorController, new MushroomField, new AttractorHUDStrategy));

	CollisionTestPair<Bullet, Mushroom>();
	CollisionTestPair<Ship, Mushroom>();

	CollisionTestPair<Bullet, FSMCentipedeBody>();
	CollisionTestPair<Bullet, FSMCentipedeHead>();
	CollisionTestPair<Ship, FSMCentipedeBody>();
	CollisionTestPair<Ship, FSMCentipedeHead>();

	CollisionTestPair<Bullet, Flea>();
	CollisionTestPair<Ship, Flea>();

	CollisionTestPair<Bullet, Scorpion>();
	CollisionTestPair<Scorpion, Mushroom>();

	CollisionTestPair<Spider, Mushroom>();
	CollisionTestPair<Spider, Ship>();
	CollisionTestPair<Spider, Bullet>();

};

// Game Objects are handled already, so just make sure all the non-GameObjects get destroyed starting from here
void Level1::Terminate()
{
	GameManager::Terminate();
	PlayerManager::Terminate();

//	Kill all the factories
	MushroomFactory::Terminate();
	FSMCentipedeFactory::Terminate();
	SpiderFactory::Terminate();
	FleaFactory::Terminate();
	ScorpionFactory::Terminate();
	EnemyExplosionFactory::Terminate();
	ShipFactory::Terminate();
	BulletFactory::Terminate();
	PlayerExplosionFactory::Terminate();
	SpawnerFactory::Terminate();
	MushroomRegeneratorFactory::Terminate();
	WaveFactory::Terminate();
	GlyphFactory::Terminate();
	SpiderScoreFactory::Terminate();

//	Kill the Utility Managers
	AudioManager::Terminate();
	ScoreManager::Terminate();
	HUDManager::Terminate();
}