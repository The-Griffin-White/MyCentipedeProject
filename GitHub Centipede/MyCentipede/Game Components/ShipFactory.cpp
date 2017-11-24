#include "ShipFactory.h"
#include "Ship.h"

ShipFactory* ShipFactory::ptrInstance = nullptr;

Ship* ShipFactory::privCreateShip()
{
	Ship* b;

	if (recycledItems.empty())
	{
//		ConsoleMsg::WriteLine("New Ship"); // For illustration purposes

		b = new Ship();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleShip);
	}
	else
	{
//		ConsoleMsg::WriteLine("Recycled Ship"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	b->Initialize();

	return b;
}

void ShipFactory::privRecycleShip(GameObject* b)
{
	recycledItems.push((Ship*)b);

	// For illustration purposes
//	ConsoleMsg::WriteLine("Recycled Ship Stack Size: " + Tools::ToString(recycledItems.size()));
}

void ShipFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

ShipFactory::~ShipFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Ships (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}