#include "CmdScoreByDistance.h"
#include <iostream>
#include "ScoreManager.h"

#include "TEAL\CommonElements.h"

CmdScoreByDistance::CmdScoreByDistance(int val, float d)
	: CmdScore(val), dist(d)
{
//	ConsoleMsg::WriteLine("Score by distance command created: if dist < " + Tools::ToString(d));
}

void CmdScoreByDistance::Execute()
{
	CmdScore::Execute();
}