#include "ScoreManager.h"

#include "CmdScore.h"
#include "CmdScoreByDistance.h"

#include "Constants.h"

#include "Player\PlayerManager.h"

ScoreManager* ScoreManager::ptrInstance = nullptr;

const float ScoreManager::SpiderDistFar = 9999.0f;				// Anything else
const float ScoreManager::SpiderDistMedium = CellSizeF * 4;		// Four cells away
const float ScoreManager::SpiderDistNear = CellSizeF;			// One cell away

CmdScore* ScoreManager::GetScoreCommand(ScoreEvents ev)
{
	CmdScore* pCmd = nullptr;
//	ConsoleMsg::WriteLine("Score Manager: Constructing score command for ");

	switch (ev)
	{
	case ScoreEvents::FleaKilled:
//		ConsoleMsg::WriteLine("FleaDeath");
		pCmd = new CmdScore( FleaDeath );
		break;
	case ScoreEvents::ScorpionKilled:
//		ConsoleMsg::WriteLine("ScorpionDeath");
		pCmd = new CmdScore( ScorpionDeath );
		break;
	case ScoreEvents::MushroomKilled:
//		ConsoleMsg::WriteLine("MushroomDeath");
		pCmd = new CmdScore( MushroomDeath );
		break;
	case ScoreEvents::MushroomPoisonKilled:
//		ConsoleMsg::WriteLine("MushroomPoisonDeath");
		pCmd = new CmdScore( MushroomPoisonDeath );
		break;
	case ScoreEvents::MushroomInjured:
//		ConsoleMsg::WriteLine("MushroomInjured");
		pCmd = new CmdScore(MushroomInjured);
		break;
	case ScoreEvents::CentipedeBodyKilled:
//		ConsoleMsg::WriteLine("CentipedeBodyDeath");
		pCmd = new CmdScore(CentipedeBodyDeath);
		break; 
	case ScoreEvents::CentipedeHeadKilled:
//		ConsoleMsg::WriteLine("CentipedeHeadDeath");
		pCmd = new CmdScore(CentipedeHeadDeath);
		break;
	default:
//		ConsoleMsg::WriteLine("<nothing>");
		break;
	}

	return pCmd;
}

void ScoreManager::AddScore(int val) 
{
//	ConsoleMsg::WriteLine("Current player score -> Add " + Tools::ToString(val) + " points.");
	// Note: Depending on implementations, this *may* need to be a strategy pattern:
	//      - regular mode: add score to current player
	//      - Critter-recall mode (level change): do nothing
	// Duly noted
	PlayerManager::IncreaseScore(val);
}

void ScoreManager::SendScoreCmd(CmdScore* c)
{
	Instance().StackCmd.push(c);
}

void ScoreManager::ProcessScores()
{
	Instance().privProcessScore();
}

void ScoreManager::privProcessScore()
{
//	ConsoleMsg::WriteLine("Processing all scores commands for this frame:");

	CmdScore* c;

	while (!StackCmd.empty())
	{
		c = StackCmd.top();
		c->Execute();

		StackCmd.pop(); 
	}
}

CmdScoreByDistance* ScoreManager::GetScoreCommand(ScoreDistanceEvents ev)
{
	CmdScoreByDistance* pCmd = nullptr;
//	ConsoleMsg::WriteLine("Score Manager: Constructing score by distance command for ");

	switch (ev)
	{
	case ScoreDistanceEvents::SpiderKilledNear:
//		ConsoleMsg::WriteLine("SpiderDeathNear");
		pCmd = new CmdScoreByDistance(SpiderDeathNear, SpiderDistNear);
		break;
	case ScoreDistanceEvents::SpiderKilledMed:
//		ConsoleMsg::WriteLine("SpiderDeathMedium");
		pCmd = new CmdScoreByDistance(SpiderDeathMedium, SpiderDistMedium);
		break;
	case ScoreDistanceEvents::SpiderKilledFar:
//		ConsoleMsg::WriteLine("SpiderDeathFar");
		pCmd = new CmdScoreByDistance(SpiderDeathFar, SpiderDistFar);
		break;
	default:
		ConsoleMsg::WriteLine("<nothing>");
		break;
	}

	return pCmd;
}

const float ScoreManager::ReturnSpiderDistFar()
{
	return SpiderDistFar;
}
const float ScoreManager::ReturnSpiderDistMed()
{
	return SpiderDistMedium;
}
const float ScoreManager::ReturnSpiderDistNear()
{
	return SpiderDistNear;
}

ScoreManager::~ScoreManager()
{
	ConsoleMsg::WriteLine("deleting scoremanager");
	while (!StackCmd.empty())
	{
		delete StackCmd.top();
		StackCmd.pop();
	}
}

void ScoreManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}