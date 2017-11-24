#include "MushroomRegeneratorFactory.h"

#include "MushroomRegenerator.h"

#include "ScoreManager.h"
#include "CmdScore.h"

#include "Audio Manager\AudioManager.h"
#include "Audio Manager\CmdAudio.h"

MushroomRegeneratorFactory* MushroomRegeneratorFactory::ptrInstance = nullptr;

MushroomRegeneratorFactory::MushroomRegeneratorFactory()
{
	pInjuredScore = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomInjured);
	pInjuredNoise = AudioManager::GetAudioCommand(AudioManager::AudioEvents::MushroomRegen);
	// Note: These commands are created once only and reused every time this game object is active
	// These commands should be deleted when the game object is deleted for good.
}

MushroomRegeneratorFactory::~MushroomRegeneratorFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled MushroomRegenerators (" + Tools::ToString(recycledMushroomRegenerator.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledMushroomRegenerator.empty())
	{
		delete recycledMushroomRegenerator.top();
		recycledMushroomRegenerator.pop();
	}
	delete pInjuredNoise;
	delete pInjuredScore;
}

void MushroomRegeneratorFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void MushroomRegeneratorFactory::privCreateMushroomRegenerator(Mushroom* m)
{
	MushroomRegenerator* b;

	if (recycledMushroomRegenerator.empty())
	{
		//		ConsoleMsg::WriteLine("New MushroomRegenerator"); // For illustration purposes

		b = new MushroomRegenerator();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleMushroomRegenerator);
	}
	else
	{
		//		ConsoleMsg::WriteLine("Recycled MushroomRegenerator"); // For illustration purposes

		b = recycledMushroomRegenerator.top();
		recycledMushroomRegenerator.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	b->Initialize(m);
}

void MushroomRegeneratorFactory::privRecycleMushroomRegenerator(GameObject* b)
{
	recycledMushroomRegenerator.push((MushroomRegenerator*)b);
	privReportMushroomRegeneratorScore();						// For lack of a better place...

	// For illustration purposes
	//	ConsoleMsg::WriteLine("Recycled MushroomRegenerator Stack Size: " + Tools::ToString(recycledMushroomRegenerator.size()));
}

void MushroomRegeneratorFactory::privReportMushroomRegeneratorScore()
{
//	ConsoleMsg::WriteLine("MushroomRegenerator Factory: Sending score command");
	ScoreManager::SendScoreCmd(Instance().pInjuredScore);
}

void MushroomRegeneratorFactory::privReportMushroomHealed()
{
	ConsoleMsg::WriteLine("Sending MushroomRegen Audio command");
	AudioManager::SendAudioCmd(Instance().pInjuredNoise);
}