#ifndef _CmdAudio
#define _CmdAudio

#include "..\CommandBased.h"
#include "..\TEAL\CommonElements.h"

class CmdAudio : public CommandBase
{
protected:
	sf::Sound* audio;	// sound to play

public:
	CmdAudio() = delete;
	CmdAudio(sf::Sound* a);

	virtual void Execute() = 0;
};

#endif