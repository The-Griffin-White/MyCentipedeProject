
#ifndef _ScoreManager
#define _ScoreManager

#include <stack>
#include "TEAL\CommonElements.h"

class CmdScore;
class CmdScoreByDistance;

class ScoreManager
{
private:
	// Score values;
	static const int FleaDeath = 200;
	static const int ScorpionDeath = 1000;
	static const int MushroomDeath = 1;
	static const int MushroomPoisonDeath = 1;
	static const int MushroomInjured = 5;

	static const int CentipedeBodyDeath = 10;
	static const int CentipedeHeadDeath = 100;

	static const int SpiderDeathFar = 300;
	static const float SpiderDistFar;

	static const int SpiderDeathMedium = 600;
	static const float SpiderDistMedium;

	static const int SpiderDeathNear = 900;
	static const float SpiderDistNear;

	std::stack<CmdScore*> StackCmd;

	static ScoreManager* ptrInstance;

	~ScoreManager();
	static ScoreManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new ScoreManager;
		return *ptrInstance;
	};
	
	void privProcessScore();	

public :
	// events
	enum class ScoreEvents { FleaKilled, ScorpionKilled, MushroomKilled, MushroomPoisonKilled, 
							MushroomInjured, CentipedeBodyKilled, CentipedeHeadKilled };
	enum class ScoreDistanceEvents { SpiderKilledNear, SpiderKilledMed, SpiderKilledFar};
	
	static void AddScore(int val);
	
	static CmdScore* GetScoreCommand(ScoreEvents ev);
	static CmdScoreByDistance* GetScoreCommand(ScoreDistanceEvents ev);

	static void SendScoreCmd(CmdScore* c);
	static void ProcessScores();
	
	static const float ReturnSpiderDistFar();
	static const float ReturnSpiderDistMed();
	static const float ReturnSpiderDistNear();

	static void Terminate();
};

#endif