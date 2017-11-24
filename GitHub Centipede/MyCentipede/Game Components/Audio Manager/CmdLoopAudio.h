#ifndef _CmdLoopAudio
#define _CmdLoopAudio

#include "CmdAudio.h"
#include "..\TEAL\CommonElements.h"

class CmdLoopAudio : public CmdAudio
{
public:
	CmdLoopAudio() = delete;
	CmdLoopAudio(sf::Sound* a);

	virtual void Execute() override;

};

#endif