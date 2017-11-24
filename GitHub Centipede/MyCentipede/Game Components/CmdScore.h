#ifndef _CmdScore
#define _CmdScore

#include "CommandBased.h"

class CmdScore : public CommandBase
{
protected:
	int points;	// points to add
	
public:
	CmdScore() = delete;
	CmdScore(int val);

    virtual void Execute() override;

};

#endif