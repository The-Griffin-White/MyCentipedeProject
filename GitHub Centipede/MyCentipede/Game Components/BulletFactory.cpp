#include "BulletFactory.h"
#include "Bullet.h"

#include "Audio Manager/AudioManager.h"
#include "Audio Manager/CmdPlayAudio.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;
int BulletFactory::currBullets = 0;

BulletFactory::BulletFactory()
{
	pFired = AudioManager::GetAudioCommand(AudioManager::AudioEvents::BulletFired);
	// Note: This command is created once only and reused every time this game object is active
	// The command should be deleted when the game object is deleted for good.
}

void BulletFactory::privCreateBullet(sf::Vector2f p, Ship* s)
{
	if (currBullets < MAXBULLETS)
	{
		Bullet* b;

		if (recycledItems.empty())
		{
//			ConsoleMsg::WriteLine("New Bullet"); // For illustration purposes

			b = new Bullet();

			// Declares that this object should be returned here (rather than deleted) when destroyed
			b->SetExternalManagement(RecycleBullet);
		}
		else
		{
//			ConsoleMsg::WriteLine("Recycled Bullet"); // For illustration purposes

			b = recycledItems.top();
			recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

									// Tell the object to register itself to the scene
			b->RegisterToCurrentScene();
		}

		activeItems.push_back(b);

//		ConsoleMsg::WriteLine("Pew! Pew!");
		b->Initialize(p, s);

		AudioManager::SendAudioCmd(Instance().pFired);

		currBullets++;
	}
	
}

void BulletFactory::privRecycleBullet(GameObject* b)
{
	currBullets--;

	activeItems.remove((Bullet*)b);

	recycledItems.push((Bullet*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Recycled Bullet Stack Size: " + Tools::ToString(recycledItems.size()));
}

void BulletFactory::privRecallBullets()
{
	for (std::list<Bullet*>::iterator it = activeItems.begin(); it != activeItems.end(); )
	{
		Bullet* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
}

void BulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

BulletFactory::~BulletFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Bullets (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delete all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}

	delete pFired;
}