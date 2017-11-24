#ifndef _EnemyExplosionpFactory
#define _EnemyExplosionpFactory

#include <stack>
#include "EnemyExplosion.h"

class CmdAudio;

class EnemyExplosionFactory
{
private:
	static EnemyExplosionFactory *ptrInstance;

	EnemyExplosionFactory();
	EnemyExplosionFactory(const EnemyExplosionFactory&) = delete;
	EnemyExplosionFactory& operator=(const EnemyExplosionFactory&) = delete;
	~EnemyExplosionFactory();

	static EnemyExplosionFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new EnemyExplosionFactory;
		return *ptrInstance;
	}

	std::stack<EnemyExplosion*> recycledItems;

	CmdAudio* pBoomAudio;

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateEnemyExplosionp(sf::Vector2f p);
	void privRecycleEnemyExplosion(GameObject *b);

public:
	static void CreateEnemyExplosion(sf::Vector2f p) { Instance().privCreateEnemyExplosionp(p); };
	static void RecycleEnemyExplosion(GameObject *b) { Instance().privRecycleEnemyExplosion(b); };

	static void Terminate();

};

#endif