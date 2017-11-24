#ifndef _SpiderFactory
#define _SpiderFactory

#include <stack>
#include "Spider.h"

class CmdScoreByDistance;
class CmdAudio;
class SpiderSpawner;

class SpiderFactory
{
private:
	static SpiderFactory *ptrInstance;

	SpiderFactory();
	SpiderFactory(const SpiderFactory&) = delete;
	SpiderFactory& operator=(const SpiderFactory&) = delete;
	~SpiderFactory();

	static SpiderFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpiderFactory;
		return *ptrInstance;
	}
	
	std::stack<Spider*> recycledSpiders;
	std::list<Spider*> activeSpiders;

	CmdScoreByDistance* pFarDeath;
	CmdScoreByDistance* pMedDeath;
	CmdScoreByDistance* pNearDeath;

	CmdAudio* pWalking;
	CmdAudio* pAllSpidersDead;

	int currNumSpiders;
	int maxNumSpiders;
	SpiderSpawner* pSpawner;

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateSpider();
	void privRecycleSpider(GameObject *b);
	void privReportSpiderDeath(sf::Vector2f SpiderPos, sf::Vector2f ShipPos);
	void privRecallSpiders();

public:
	static void CreateSpider() { Instance().privCreateSpider(); };
	static void RecycleSpider(GameObject *b) { Instance().privRecycleSpider(b); }
	static void ReportSpiderDeath(sf::Vector2f SpiderPos, sf::Vector2f ShipPos) { Instance().privReportSpiderDeath(SpiderPos, ShipPos); };
	static void RecallSpiders() { Instance().privRecallSpiders(); };

	static void GetMaxNumSpiders(int num);
	static void GetSpawnerPointer(SpiderSpawner* p);

	static void Terminate();

};

#endif