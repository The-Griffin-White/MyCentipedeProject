#ifndef _BulletFactory
#define _BulletFactory

#include <stack>
#include "Bullet.h"

class CmdAudio;
class Ship;

class BulletFactory
{
private:
	static BulletFactory *ptrInstance;

	BulletFactory();
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory();

	static BulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory;
		return *ptrInstance;
	}

	CmdAudio* pFired;

	static const int MAXBULLETS = 1;
	static int currBullets;
	std::stack<Bullet*> recycledItems;
	std::list<Bullet*> activeItems;

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateBullet(sf::Vector2f p, Ship* s);
	void privRecycleBullet(GameObject *b);
	void privRecallBullets();

public:
	static void CreateBullet(sf::Vector2f p, Ship* s) { Instance().privCreateBullet(p, s); };
	static void RecycleBullet(GameObject *b) { Instance().privRecycleBullet(b); };
	static void RecallBullets() { Instance().privRecallBullets(); };

	static void Terminate();

};

#endif