#include "SpiderScoreFactory.h"

#include "SpiderScore.h"

SpiderScoreFactory* SpiderScoreFactory::ptrInstance = nullptr;

SpiderScoreFactory::SpiderScoreFactory()
{
}

SpiderScoreFactory::~SpiderScoreFactory()
{
	// These should be empty already by the time we destroy this singleton...
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
	while (!activeItems.empty())
	{
		delete activeItems.back();
		activeItems.pop_back();
	}
}

void SpiderScoreFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

SpiderScore* SpiderScoreFactory::privCreateSpiderScore()
{
	SpiderScore* b;

	if (recycledItems.empty())
	{
		//		ConsoleMsg::WriteLine("New Spider Score"); // For illustration purposes

		b = new SpiderScore();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleSpiderScore);
	}
	else
	{
		//		ConsoleMsg::WriteLine("Recycled Spider"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

								// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	activeItems.push_back(b);

	return b;
}

void SpiderScoreFactory::privCreateSpiderScoreNear(sf::Vector2f p)
{
	privCreateSpiderScore()->Initialize(p, ScoreNumber::Near);
}

void SpiderScoreFactory::privCreateSpiderScoreMedium(sf::Vector2f p)
{
	privCreateSpiderScore()->Initialize(p, ScoreNumber::Medium);
}

void SpiderScoreFactory::privCreateSpiderScoreFar(sf::Vector2f p)
{
	privCreateSpiderScore()->Initialize(p, ScoreNumber::Far);
}

void SpiderScoreFactory::privRecycleSpiderScore(GameObject *b)
{
	activeItems.remove((SpiderScore*)b);

	recycledItems.push((SpiderScore*)b);
}

void SpiderScoreFactory::privRecallSpiderScores()
{
	for (std::list<SpiderScore*>::iterator it = activeItems.begin(); it != activeItems.end(); )
	{
		SpiderScore* currItem = *it;
		++it;
		currItem->MarkForDestroy();
	}
}