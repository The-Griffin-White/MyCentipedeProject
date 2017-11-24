#include "ScorpionFactory.h"
#include "Scorpion.h"

#include "ScoreManager.h"
#include "CmdScore.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"


#include "ScorpionSpawner.h"

ScorpionFactory* ScorpionFactory::ptrInstance = nullptr;

ScorpionFactory::ScorpionFactory()
{
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::ScorpionKilled);

	pWalking = AudioManager::GetAudioCommand(AudioManager::AudioEvents::ScorpionWalking);
	pAllScorpionsDead = AudioManager::GetAudioCommand(AudioManager::AudioEvents::StopScorpionWalking);
	// Note: This command is created once only and reused every time this game object is active
	// The command should be deleted when the game object is deleted for good.

	currNumScorpions = 0;
	maxNumScorpions = 1000;					// Some number we'll never reach
	pSpawner = nullptr;
}

void ScorpionFactory::privCreateScorpion()
{
	Scorpion* b;

	if (recycledScorpions.empty())
	{
//		ConsoleMsg::WriteLine("New Scorpion"); // For illustration purposes

		b = new Scorpion();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleScorpion);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled Scorpion"); // For illustration purposes

		b = recycledScorpions.top();
		recycledScorpions.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	int row = rand() % (TopPlayerRow);

	if (rand() % 2 == 1)
		b->Initialize(row, Left);
	else
		b->Initialize(row, Right);

	activeScorpions.push_back(b);

	currNumScorpions++;
	if (currNumScorpions == 1)
	{
		AudioManager::SendAudioCmd(pWalking);
	}
	if (currNumScorpions == maxNumScorpions)
	{
		if (pSpawner)
			pSpawner->MaxNumReached();
	}
}

void ScorpionFactory::privRecycleScorpion(GameObject *b)
{
	if (currNumScorpions == 1)
	{
		AudioManager::SendAudioCmd(pAllScorpionsDead);
	}
	if (currNumScorpions == maxNumScorpions)
	{
		if (pSpawner)
			pSpawner->BelowMaxNum();
	}
	currNumScorpions--;

	activeScorpions.remove((Scorpion*)b);

	recycledScorpions.push((Scorpion*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Scorpion Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

void ScorpionFactory::privRecallScorpions()
{
	AudioManager::SendAudioCmd(pAllScorpionsDead);
	for (std::list<Scorpion*>::iterator it = activeScorpions.begin(); it != activeScorpions.end(); )
	{
		Scorpion* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
}

void ScorpionFactory::privReportScorpionDeath()
{
//	ConsoleMsg::WriteLine("Scorpion Factory: Sending death score command");
	ScoreManager::SendScoreCmd(Instance().pDeath);
}

void ScorpionFactory::GetMaxNumScorpions(int num)
{
	Instance().maxNumScorpions = num;
}

void ScorpionFactory::GetSpawnerPointer(ScorpionSpawner* p)
{
	Instance().pSpawner = p;
}

void ScorpionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

ScorpionFactory::~ScorpionFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Scorpions (" + Tools::ToString(recycledScorpions.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledScorpions.empty())
	{
		delete recycledScorpions.top();
		recycledScorpions.pop();
	}

	delete pDeath;

	delete pWalking;
	delete pAllScorpionsDead;
}