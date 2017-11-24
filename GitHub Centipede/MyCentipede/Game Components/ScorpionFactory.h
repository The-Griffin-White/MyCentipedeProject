#ifndef _ScorpionFactory
#define _ScorpionFactory

#include <stack>
#include "TEAL\CommonElements.h"
//#include "Scorpion.h"

class Scorpion;
class CmdScore;
class CmdAudio;
class ScorpionSpawner;

class ScorpionFactory
{
private:
	static ScorpionFactory *ptrInstance;

	ScorpionFactory();
	ScorpionFactory(const ScorpionFactory&) = delete;
	ScorpionFactory& operator=(const ScorpionFactory&) = delete;
	~ScorpionFactory();

	static ScorpionFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScorpionFactory;
		return *ptrInstance;
	}

	std::stack<Scorpion*> recycledScorpions;
	std::list<Scorpion*> activeScorpions;

	CmdScore* pDeath;
	CmdAudio* pWalking;
	CmdAudio* pAllScorpionsDead;

	int currNumScorpions;
	int maxNumScorpions;
	ScorpionSpawner* pSpawner;

	// Private NON_STATIC methods to perform actual work on member var
	void privCreateScorpion();
	void privRecycleScorpion(GameObject *b);
	void privReportScorpionDeath();
	void privRecallScorpions();

public:
	static void CreateScorpion() { Instance().privCreateScorpion(); };
	static void RecycleScorpion(GameObject *b) { Instance().privRecycleScorpion(b); };
	static void ReportScorpionDeath() { Instance().privReportScorpionDeath(); };
	static void RecallScorpions() { Instance().privRecallScorpions(); };

	static void GetMaxNumScorpions(int num);
	static void GetSpawnerPointer(ScorpionSpawner* p);

	static void Terminate();

};

#endif