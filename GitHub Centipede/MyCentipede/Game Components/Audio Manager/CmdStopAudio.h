#ifndef _CmdStopAudio
#define _CmdStopAudio

#include "CmdAudio.h"
#include "..\TEAL\CommonElements.h"

class CmdStopAudio : public CmdAudio
{
public:
	CmdStopAudio() = delete;
	CmdStopAudio(sf::Sound* a);

	virtual void Execute() override;

};

#endif