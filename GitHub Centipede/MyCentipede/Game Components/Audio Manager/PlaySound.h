#ifndef _PlaySound
#define _PlaySound

#include "PlayAudioStrategy.h"
#include "AudioManager.h"

class PlaySound : public PlayAudioStrategy
{
public:
	virtual void Play(CmdAudio* c) override { AudioManager::PushAudioCmd(c); };
};

#endif