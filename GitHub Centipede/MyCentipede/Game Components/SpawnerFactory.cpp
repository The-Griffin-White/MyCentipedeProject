#include "SpawnerFactory.h"

#include "CentipedeSpawner.h"
#include "FleaSpawner.h"
#include "ScorpionSpawner.h"
#include "SpiderSpawner.h"

SpawnerFactory* SpawnerFactory::ptrInstance = nullptr;


SpawnerFactory::~SpawnerFactory()
{
	ConsoleMsg::WriteLine("deleting spawnerfactory");
	while (!recycledCentipedeSpawners.empty())
		recycledCentipedeSpawners.pop();

	while (!recycledFleaSpawners.empty())
		recycledFleaSpawners.pop();

	while (!recycledScorpionSpawners.empty())
		recycledScorpionSpawners.pop();

	while (!recycledSpiderSpawners.empty())
		recycledSpiderSpawners.pop();
}

void SpawnerFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

CentipedeSpawner* SpawnerFactory::GrabCentipedeSpawner()
{
	CentipedeSpawner* b;

	if (recycledCentipedeSpawners.empty())
	{
		//		ConsoleMsg::WriteLine("New Mushroom"); // For illustration purposes

		b = new CentipedeSpawner();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleCentipedeSpawner);
	}
	else
	{
		//		ConsoleMsg::WriteLine("Recycled Mushroom"); // For illustration purposes

		b = recycledCentipedeSpawners.top();
		recycledCentipedeSpawners.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

CentipedeSpawner* SpawnerFactory::privCreateCentipedeSpawner()
{
	CentipedeSpawner* b = GrabCentipedeSpawner();
	b->Initialize();
	return b;
}

CentipedeSpawner* SpawnerFactory::privCreateCentipedeSpawner(bool soloHead, int numSegments)
{
	CentipedeSpawner* b = GrabCentipedeSpawner();
	b->Initialize(soloHead, numSegments);
	return b;
}

FleaSpawner* SpawnerFactory::GrabFleaSpawner()
{
	FleaSpawner* b;

	if (recycledFleaSpawners.empty())
	{
		//		ConsoleMsg::WriteLine("New Mushroom"); // For illustration purposes

		b = new FleaSpawner();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleFleaSpawner);
	}
	else
	{
		//		ConsoleMsg::WriteLine("Recycled Mushroom"); // For illustration purposes

		b = recycledFleaSpawners.top();
		recycledFleaSpawners.pop();	// Remember: top doesn't pop and pop returns void...

											// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

FleaSpawner* SpawnerFactory::privCreateFleaSpawner()
{
	FleaSpawner* b = GrabFleaSpawner();
	b->Initialize();
	return b;
}

FleaSpawner* SpawnerFactory::privCreateFleaSpawner(int cap)
{
	FleaSpawner* b = GrabFleaSpawner();
	b->Initialize(cap);
	return b;
}

ScorpionSpawner* SpawnerFactory::GrabScorpionSpawner()
{
	ScorpionSpawner* b;

	if (recycledScorpionSpawners.empty())
	{
		//		ConsoleMsg::WriteLine("New Mushroom"); // For illustration purposes

		b = new ScorpionSpawner();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleScorpionSpawner);
	}
	else
	{
		//		ConsoleMsg::WriteLine("Recycled Mushroom"); // For illustration purposes

		b = recycledScorpionSpawners.top();
		recycledScorpionSpawners.pop();	// Remember: top doesn't pop and pop returns void...

									// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

ScorpionSpawner* SpawnerFactory::privCreateScorpionSpawner()
{
	ScorpionSpawner* b = GrabScorpionSpawner();
	b->Initialize();
	return b;
}

ScorpionSpawner* SpawnerFactory::privCreateScorpionSpawner(int probability, int cap)
{
	ScorpionSpawner* b = GrabScorpionSpawner();
	b->Initialize(probability, cap);
	return b;
}

SpiderSpawner* SpawnerFactory::GrabSpiderSpawner()
{
	SpiderSpawner* b;

	if (recycledSpiderSpawners.empty())
	{
		//		ConsoleMsg::WriteLine("New Mushroom"); // For illustration purposes

		b = new SpiderSpawner();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleSpiderSpawner);
	}
	else
	{
		//		ConsoleMsg::WriteLine("Recycled Mushroom"); // For illustration purposes

		b = recycledSpiderSpawners.top();
		recycledSpiderSpawners.pop();	// Remember: top doesn't pop and pop returns void...

									// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

SpiderSpawner* SpawnerFactory::privCreateSpiderSpawner()
{
	SpiderSpawner* b = GrabSpiderSpawner();
	b->Initialize();
	return b;
}

SpiderSpawner* SpawnerFactory::privCreateSpiderSpawner(int probability, int cap)
{
	SpiderSpawner* b = GrabSpiderSpawner();
	b->Initialize(probability, cap);
	return b;
}

void SpawnerFactory::privRecycleCentipedeSpawner(GameObject* b)
{
	recycledCentipedeSpawners.push((CentipedeSpawner*)b);
}
void SpawnerFactory::privRecycleFleaSpawner(GameObject* b)
{
	recycledFleaSpawners.push((FleaSpawner*)b);
}
void SpawnerFactory::privRecycleScorpionSpawner(GameObject* b)
{
	recycledScorpionSpawners.push((ScorpionSpawner*)b);
}
void SpawnerFactory::privRecycleSpiderSpawner(GameObject* b)
{
	recycledSpiderSpawners.push((SpiderSpawner*)b);
}