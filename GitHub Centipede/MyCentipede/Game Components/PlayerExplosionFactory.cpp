#include "PlayerExplosionFactory.h"
#include "PlayerExplosion.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"

PlayerExplosionFactory* PlayerExplosionFactory::ptrInstance = nullptr;

PlayerExplosionFactory::PlayerExplosionFactory()
{
	pBoomAudio = AudioManager::GetAudioCommand(AudioManager::AudioEvents::PlayerExplosion);
}

void PlayerExplosionFactory::privCreatePlayerExplosionp(sf::Vector2f p)
{
	PlayerExplosion* b;

	if (recycledItems.empty())
	{
//		ConsoleMsg::WriteLine("New PlayerExplosion"); // For illustration purposes

		b = new PlayerExplosion();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecyclePlayerExplosion);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled PlayerExplosion"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	AudioManager::SendAudioCmd(Instance().pBoomAudio);

	b->Initialize(p);
}

void PlayerExplosionFactory::privRecyclePlayerExplosion(GameObject* b)
{
	recycledItems.push((PlayerExplosion*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Recycled PlayerExplosion Stack Size: " + Tools::ToString(recycledItems.size()));
}

void PlayerExplosionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

PlayerExplosionFactory::~PlayerExplosionFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled PlayerExplosion (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}

	delete pBoomAudio;
}