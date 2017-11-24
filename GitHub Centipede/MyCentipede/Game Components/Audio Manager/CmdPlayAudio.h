#ifndef _CmdPlayAudio
#define _CmdPlayAudio

#include "CmdAudio.h"
#include "..\TEAL\CommonElements.h"

class CmdPlayAudio : public CmdAudio
{	
public:
	CmdPlayAudio() = delete;
	CmdPlayAudio(sf::Sound* a);

    virtual void Execute() override;

};

#endif