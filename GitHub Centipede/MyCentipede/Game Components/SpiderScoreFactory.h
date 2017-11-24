#ifndef _SpiderScoreFactory
#define _SpiderScoreFactory

#include <stack>
#include <list>
#include "TEAL/CommonElements.h"

class SpiderScore;

class SpiderScoreFactory
{
private:
	static SpiderScoreFactory *ptrInstance;

	SpiderScoreFactory();
	SpiderScoreFactory(const SpiderScoreFactory&) = delete;
	SpiderScoreFactory& operator=(const SpiderScoreFactory&) = delete;
	~SpiderScoreFactory();

	static SpiderScoreFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpiderScoreFactory;
		return *ptrInstance;
	}

	std::stack<SpiderScore*> recycledItems;
	std::list<SpiderScore*> activeItems;

	// Private NON_STATIC methods to perform actual work on member var
	SpiderScore* privCreateSpiderScore();

	void privCreateSpiderScoreNear(sf::Vector2f p);
	void privCreateSpiderScoreMedium(sf::Vector2f p);
	void privCreateSpiderScoreFar(sf::Vector2f p);
	void privRecycleSpiderScore(GameObject *b);
	void privRecallSpiderScores();

public:
	static void CreateSpiderScoreNear(sf::Vector2f p) { Instance().privCreateSpiderScoreNear(p); };
	static void CreateSpiderScoreMedium(sf::Vector2f p) { Instance().privCreateSpiderScoreMedium(p); };
	static void CreateSpiderScoreFar(sf::Vector2f p) { Instance().privCreateSpiderScoreFar(p); };
	static void RecycleSpiderScore(GameObject *b) { Instance().privRecycleSpiderScore(b); }
	static void RecallSpiderScores() { Instance().privRecallSpiderScores(); };

	static void Terminate();

};

#endif