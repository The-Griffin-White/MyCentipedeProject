#ifndef _PlayNothing
#define _PlayNothing

#include "PlayAudioStrategy.h"

class PlayNothing : public PlayAudioStrategy
{
public:
	virtual void Play(CmdAudio* c) override {};
};

#endif