#ifndef _PlayAudioStrategy
#define _PlayAudioStrategy

class CmdAudio;

class PlayAudioStrategy
{
public:
	virtual void Play(CmdAudio* c) = 0;
};

#endif