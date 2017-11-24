#include "CmdScore.h"
#include <iostream>
#include "ScoreManager.h"

#include "TEAL\CommonElements.h"

CmdScore::CmdScore( int val)
	:  points(val)
{
//	ConsoleMsg::WriteLine("Score Command created: Points = " + Tools::ToString(val));
}

void CmdScore::Execute()
{
	ScoreManager::AddScore(points);
}