#include "CmdLoopAudio.h"
#include "AudioManager.h"

CmdLoopAudio::CmdLoopAudio(sf::Sound* a)
	: CmdAudio(a)
{
}

void CmdLoopAudio::Execute()
{
	AudioManager::LoopAudio(audio);
}