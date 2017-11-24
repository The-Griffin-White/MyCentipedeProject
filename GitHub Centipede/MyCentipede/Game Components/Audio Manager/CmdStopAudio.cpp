#include "CmdStopAudio.h"
#include "AudioManager.h"

CmdStopAudio::CmdStopAudio(sf::Sound* a)
	: CmdAudio(a)
{
}

void CmdStopAudio::Execute()
{
	AudioManager::StopAudio(audio);
}