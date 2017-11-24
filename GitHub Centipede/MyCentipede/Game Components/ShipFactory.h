#ifndef _ShipFactory
#define _ShipFactory

#include <stack>
#include "Ship.h"

class ShipFactory
{
private:
	static ShipFactory *ptrInstance;

	ShipFactory() { };
	ShipFactory(const ShipFactory&) = delete;
	ShipFactory& operator=(const ShipFactory&) = delete;
	~ShipFactory();

	static ShipFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ShipFactory;
		return *ptrInstance;
	}

	std::stack<Ship*> recycledItems;

	// Private NON_STATIC methods to perform actual work on member var
	Ship* privCreateShip();
	void privRecycleShip(GameObject *b);

public:
	static Ship* CreateShip() { return Instance().privCreateShip(); };
	static void RecycleShip(GameObject *b) { Instance().privRecycleShip(b); };

	static void Terminate();

};

#endif