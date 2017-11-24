#include "CmdPlayAudio.h"
#include "AudioManager.h"

CmdPlayAudio::CmdPlayAudio(sf::Sound* a)
	:  CmdAudio(a)
{
}

void CmdPlayAudio::Execute()
{
	AudioManager::PlayAudio(audio);
}