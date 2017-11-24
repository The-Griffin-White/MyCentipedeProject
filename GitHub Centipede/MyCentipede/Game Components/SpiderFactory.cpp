#include "SpiderFactory.h"
#include "Direction.h"

#include "ScoreManager.h"
#include "CmdScoreByDistance.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"

#include "SpiderScoreFactory.h"

#include "SpiderSpawner.h"

SpiderFactory* SpiderFactory::ptrInstance = nullptr;

SpiderFactory::SpiderFactory()
{
	pFarDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreDistanceEvents::SpiderKilledFar);
	pMedDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreDistanceEvents::SpiderKilledMed);
	pNearDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreDistanceEvents::SpiderKilledNear);

	pWalking = AudioManager::GetAudioCommand(AudioManager::AudioEvents::SpiderWalking);
	pAllSpidersDead = AudioManager::GetAudioCommand(AudioManager::AudioEvents::StopSpiderWalking);
	// Note: This command is created once only and reused every time this game object is active
	// The command should be deleted when the game object is deleted for good.

	currNumSpiders = 0;
	maxNumSpiders = 1000;					// Some number we'll never reach
	pSpawner = nullptr;
}

void SpiderFactory::privCreateSpider()
{
	Spider* b;

	if (recycledSpiders.empty())
	{
//		ConsoleMsg::WriteLine("New Spider"); // For illustration purposes

		b = new Spider();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleSpider);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled Spider"); // For illustration purposes

		b = recycledSpiders.top();
		recycledSpiders.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}


	if (rand() % 2 == 1)
		b->Initialize(Left);
	else
		b->Initialize(Right);

	activeSpiders.push_back(b);

	currNumSpiders++;
	if (currNumSpiders == 1)
	{
		AudioManager::SendAudioCmd(pWalking);
	}
	if (currNumSpiders >= maxNumSpiders)
	{
		if (pSpawner)
			pSpawner->MaxNumReached();
	}
}

void SpiderFactory::privReportSpiderDeath(sf::Vector2f SpiderPos, sf::Vector2f ShipPos)
{
	// Deliberate choice. I don't want the score to be based on horizontal distance, but vertical, since thats what makes it risky
	// We already assume that the player was on the same x-axis when fired, no need to encourage them staying there
	// I guess this is game design choice so idk
	float dist = ShipPos.y - SpiderPos.y;
	if (dist <= pNearDeath->GetDistance())
	{
//		ConsoleMsg::WriteLine("Spider Factory: Sending Near death score command");
		ScoreManager::SendScoreCmd(Instance().pNearDeath);
		SpiderScoreFactory::CreateSpiderScoreNear(SpiderPos);
	}
	else if (dist <= pMedDeath->GetDistance())
	{
//		ConsoleMsg::WriteLine("Spider Factory: Sending medium death score command");
		ScoreManager::SendScoreCmd(Instance().pMedDeath);
		SpiderScoreFactory::CreateSpiderScoreMedium(SpiderPos);
	}
	else
	{
//		ConsoleMsg::WriteLine("Spider Factory: Sending far death score command");
		ScoreManager::SendScoreCmd(Instance().pFarDeath);
		SpiderScoreFactory::CreateSpiderScoreFar(SpiderPos);
	}
}

void SpiderFactory::GetMaxNumSpiders(int num)
{
	Instance().maxNumSpiders = num;
}

void SpiderFactory::GetSpawnerPointer(SpiderSpawner* p)
{
	Instance().pSpawner = p;
}

void SpiderFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void SpiderFactory::privRecycleSpider(GameObject* b)
{
	if (currNumSpiders == 1)
	{
		AudioManager::SendAudioCmd(pAllSpidersDead);
	}
	if (currNumSpiders == maxNumSpiders)
	{
		if (pSpawner)
			pSpawner->BelowMaxNum();
	}
	currNumSpiders--;

	activeSpiders.remove((Spider*)b);

	recycledSpiders.push((Spider*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Spider Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

void SpiderFactory::privRecallSpiders()
{
	AudioManager::SendAudioCmd(pAllSpidersDead);
	for (std::list<Spider*>::iterator it = activeSpiders.begin(); it != activeSpiders.end(); )
	{
		Spider* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
}

SpiderFactory::~SpiderFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Spiders (" + Tools::ToString(recycledSpiders.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledSpiders.empty())
	{
		delete recycledSpiders.top();
		recycledSpiders.pop();
	}

	delete pFarDeath;
	delete pMedDeath;
	delete pNearDeath;

	delete pWalking;
	delete pAllSpidersDead;
}