#include "MushroomFactory.h"
#include "Mushroom.h"

#include "ScoreManager.h"
#include "CmdScore.h"

MushroomFactory* MushroomFactory::ptrInstance = nullptr;

MushroomFactory::MushroomFactory()
{
	pDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomKilled);
	// Note: These commands are created once only and reused every time this game object is active
	// These commands should be deleted when the game object is deleted for good.
}

Mushroom* MushroomFactory::privCreateMushroom(sf::Vector2f p, MushroomField *g, int i, int j)
{
	Mushroom* b;

	if (recycledItems.empty())
	{
//		ConsoleMsg::WriteLine("New Mushroom"); // For illustration purposes

		b = new Mushroom();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleMushroom);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled Mushroom"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	b->Initialize( p, g, i, j);

	return b;
}

void MushroomFactory::privRecycleMushroom(GameObject* b)
{
	recycledItems.push((Mushroom*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Recycled Mushroom Stack Size: " + Tools::ToString(recycledItems.size()));
}

void MushroomFactory::privReportMushroomDeath()
{
	printf("Mushroom Factory: Sending death score command\n");
	ScoreManager::SendScoreCmd(Instance().pDeath);
}

void MushroomFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

MushroomFactory::~MushroomFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Mushrooms (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}

	delete pDeath;
}