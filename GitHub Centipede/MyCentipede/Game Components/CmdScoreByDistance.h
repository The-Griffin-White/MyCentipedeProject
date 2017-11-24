#ifndef _CmdScoreByDistance
#define _CmdScoreByDistance

#include "CmdScore.h"

class CmdScoreByDistance : public CmdScore
{
private:
	float dist;

public:
	CmdScoreByDistance() = delete;
	CmdScoreByDistance(int val, float d);

	float GetDistance() { return dist; }

	virtual void Execute() override;


};

#endif