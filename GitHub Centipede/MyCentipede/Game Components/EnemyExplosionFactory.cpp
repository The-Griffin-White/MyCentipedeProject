#include "EnemyExplosionFactory.h"
#include "EnemyExplosion.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"

EnemyExplosionFactory* EnemyExplosionFactory::ptrInstance = nullptr;

EnemyExplosionFactory::EnemyExplosionFactory()
{
	pBoomAudio = AudioManager::GetAudioCommand(AudioManager::AudioEvents::EnemyExplosion);
}

void EnemyExplosionFactory::privCreateEnemyExplosionp(sf::Vector2f p)
{
	EnemyExplosion* b;

	if (recycledItems.empty())
	{
//		ConsoleMsg::WriteLine("New EnemyExplosion"); // For illustration purposes

		b = new EnemyExplosion();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleEnemyExplosion);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled EnemyExplosion"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	AudioManager::SendAudioCmd(Instance().pBoomAudio);

	b->Initialize(p);
}

void EnemyExplosionFactory::privRecycleEnemyExplosion(GameObject* b)
{
	recycledItems.push((EnemyExplosion*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Recycled EnemyExplosion Stack Size: " + Tools::ToString(recycledItems.size()));
}

void EnemyExplosionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

EnemyExplosionFactory::~EnemyExplosionFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled EnemyExplosion (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}

	delete pBoomAudio;
}