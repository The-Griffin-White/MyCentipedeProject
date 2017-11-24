#ifndef _CommandBase
#define _CommandBase

class CommandBase
{
public:
	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute() = 0;
};

#endif