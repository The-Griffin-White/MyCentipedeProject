#include "FleaFactory.h"
#include "Flea.h"

#include "ScoreManager.h"
#include "CmdScore.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"

#include "FleaSpawner.h"

FleaFactory* FleaFactory::ptrInstance = nullptr;

FleaFactory::FleaFactory()
{
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::FleaKilled);
	pFalling = AudioManager::GetAudioCommand(AudioManager::AudioEvents::FleaFalling);
	pAllFleasDead = AudioManager::GetAudioCommand(AudioManager::AudioEvents::StopFleaFalling);
	// Note: This command is created once only and reused every time this game object is active
	// The command should be deleted when the game object is deleted for good.

	currNumFleas = 0;
	maxNumFleas = 1000;					// Some number we shouldnt reach anyway
	pSpawner = nullptr;	
}

void FleaFactory::privCreateFlea()
{
	Flea* b;

	if (recycledFleas.empty())
	{
//		ConsoleMsg::WriteLine("New Flea"); // For illustration purposes

		b = new Flea();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleFlea);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled Flea"); // For illustration purposes

		b = recycledFleas.top();
		recycledFleas.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	int col = rand() % FieldDimensions;

	b->Initialize(col);

	activeFleas.push_back(b);

	currNumFleas++;
	if (currNumFleas == 1)
	{
		AudioManager::SendAudioCmd(pFalling);
	}
	if (currNumFleas == maxNumFleas)
	{
		if (pSpawner)
			pSpawner->MaxNumReached();
	}
}

void FleaFactory::privRecycleFlea(GameObject* b)
{
	if (currNumFleas == 1)
	{
		AudioManager::SendAudioCmd(pAllFleasDead);
	}
	if (currNumFleas == maxNumFleas)
	{
		if (pSpawner)
			pSpawner->BelowMaxNum();
	}
	currNumFleas--;

	activeFleas.remove((Flea*)b);

	recycledFleas.push((Flea*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Recycled Flea Stack Size: " + Tools::ToString(recycledItems.size()));
}

void FleaFactory::privRecallFleas()
{
	AudioManager::SendAudioCmd(pAllFleasDead);
	for (std::list<Flea*>::iterator it = activeFleas.begin(); it != activeFleas.end(); ) 
	{
		Flea* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
}

void FleaFactory::privReportFleaDeath()
{
//	ConsoleMsg::WriteLine("Flea Factory: Sending death score command");
	ScoreManager::SendScoreCmd(Instance().pDeath);
}

void FleaFactory::GetMaxNumFleas(int num)
{
	Instance().maxNumFleas = num;
}

void FleaFactory::GetSpawnerPointer(FleaSpawner* p)
{
	Instance().pSpawner = p;
}

void FleaFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

FleaFactory::~FleaFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Fleas (" + Tools::ToString(recycledFleas.size()) + ")");

	// forcefully delete all recycled gameobjects
	while (!recycledFleas.empty())
	{
		delete recycledFleas.top();
		recycledFleas.pop();
	}

	delete pDeath;
	delete pFalling;
	delete pAllFleasDead;
}