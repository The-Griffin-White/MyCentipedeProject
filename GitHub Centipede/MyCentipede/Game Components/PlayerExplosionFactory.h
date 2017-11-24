#ifndef _PlayerExplosionpFactory
#define _PlayerExplosionFactory

#include <stack>
#include "PlayerExplosion.h"

class CmdAudio;

class PlayerExplosionFactory
{
private:
	static PlayerExplosionFactory *ptrInstance;

	PlayerExplosionFactory();
	PlayerExplosionFactory(const PlayerExplosionFactory&) = delete;
	PlayerExplosionFactory& operator=(const PlayerExplosionFactory&) = delete;
	~PlayerExplosionFactory();

	static PlayerExplosionFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerExplosionFactory;
		return *ptrInstance;
	}

	std::stack<PlayerExplosion*> recycledItems;

	CmdAudio* pBoomAudio;

	// Private NON_STATIC methods to perform actual work on member var
	void privCreatePlayerExplosionp(sf::Vector2f p);
	void privRecyclePlayerExplosion(GameObject *b);

public:
	static void CreatePlayerExplosion(sf::Vector2f p) { Instance().privCreatePlayerExplosionp(p); };
	static void RecyclePlayerExplosion(GameObject *b) { Instance().privRecyclePlayerExplosion(b); };

	static void Terminate();

};

#endif