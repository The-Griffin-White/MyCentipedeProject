#ifndef _MushroomFactory
#define _MushroomFactory

#include <stack>
#include "Mushroom.h"

class MushroomField;
class CmdScore;

class MushroomFactory
{
private:
	static MushroomFactory *ptrInstance;

	MushroomFactory();
	MushroomFactory(const MushroomFactory&) = delete;
	MushroomFactory& operator=(const MushroomFactory&) = delete;
	~MushroomFactory();

	static MushroomFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new MushroomFactory;
		return *ptrInstance;
	}

	std::stack<Mushroom*> recycledItems;

	CmdScore* pDeath;

	// Private NON_STATIC methods to perform actual work on member var
	Mushroom* privCreateMushroom(sf::Vector2f p, MushroomField *g, int i, int j);
	void privRecycleMushroom(GameObject *b);
	void privReportMushroomDeath();

public:
	static Mushroom* CreateMushroom(sf::Vector2f p, MushroomField *g, int i, int j) { return Instance().privCreateMushroom(p, g, i, j); };
	static void RecycleMushroom(GameObject *b) { Instance().privRecycleMushroom(b); };
	static void ReportMushroomDeath() { Instance().privReportMushroomDeath(); };

	static void Terminate();

};

#endif