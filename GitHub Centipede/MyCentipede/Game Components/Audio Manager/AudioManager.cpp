#include "AudioManager.h"

#include "CmdPlayAudio.h"
#include "CmdLoopAudio.h"
#include "CmdStopAudio.h"

#include "..\Constants.h"

#include "PlaySound.h"
#include "PlayNothing.h"

//sf::Sound* AudioManager::aBulletFired = new sf::Sound(ResourceManager::GetSound("Fire"));

AudioManager* AudioManager::ptrInstance = nullptr;

AudioManager::AudioManager()
{
	Silent = new PlayNothing;
	Play = new PlaySound;
	pAudio = Silent;


	aBulletFired = new sf::Sound(ResourceManager::GetSound("Fire"));
	aBulletFired->setVolume(Bullet_Fire_Sound_Volume);
	aBulletFired->setPitch(Bullet_Fire_Sound_Pitch);

	aPlayerExplosion = new sf::Sound(ResourceManager::GetSound("PlayerDeath"));
	aPlayerExplosion->setVolume(Ship_Explosion_Sound_Volume);
	aPlayerExplosion->setPitch(Ship_Explosion_Sound_Pitch);

	aEnemyExplosion = new sf::Sound(ResourceManager::GetSound("Kill"));
	aEnemyExplosion->setVolume(Kill_Sound_Volume);
	aEnemyExplosion->setPitch(Kill_Sound_Pitch);

	aCentipedeWalking = new sf::Sound(ResourceManager::GetSound("Centipede"));
	aCentipedeWalking->setVolume(Centipede_Move_Sound_Volume);
	aCentipedeWalking->setPitch(Centipede_Move_Sound_Pitch);

	aMushroomRegen = new sf::Sound(ResourceManager::GetSound("MushroomBonus"));
	aMushroomRegen->setVolume(MushroomRegen_Sound_Volume);
	aMushroomRegen->setPitch(MushroomRegen_Sound_Pitch);

	aFleaFalling = new sf::Sound(ResourceManager::GetSound("Flea"));
	aFleaFalling->setVolume(Flea_Move_Sound_Volume);
	aFleaFalling->setPitch(Flea_Move_Sound_Pitch);

	aSpiderWalking = new sf::Sound(ResourceManager::GetSound("Spider"));
	aSpiderWalking->setVolume(Spider_Move_Sound_Volume);
	aSpiderWalking->setPitch(Spider_Move_Sound_Pitch);

	aScorpionWalking = new sf::Sound(ResourceManager::GetSound("Scorpion"));
	aScorpionWalking->setVolume(Scorpion_Move_Sound_Volume);
	aScorpionWalking->setPitch(Scorpion_Move_Sound_Pitch);

}

CmdAudio* AudioManager::GetAudioCommand(AudioEvents ev)
{
	CmdAudio* pCmd = nullptr;
	ConsoleMsg::WriteLine("Score Manager: Constructing score command for ");

	switch (ev)
	{
	case AudioEvents::BulletFired:
		ConsoleMsg::WriteLine("BulletFired noise triggered");
		pCmd = new CmdPlayAudio( Instance().aBulletFired );
		break;
	case AudioEvents::PlayerExplosion:
		ConsoleMsg::WriteLine("PlayerExplosion noise triggered");
		pCmd = new CmdPlayAudio(Instance().aPlayerExplosion);
		break;
	case AudioEvents::EnemyExplosion:
		ConsoleMsg::WriteLine("EnemyExplosion noise triggered");
		pCmd = new CmdPlayAudio(Instance().aEnemyExplosion);
		break;
	case AudioEvents::CentipedeWalking:
		ConsoleMsg::WriteLine("CentipedeWalking noise triggered");
		pCmd = new CmdLoopAudio(Instance().aCentipedeWalking);
		break;
	case AudioEvents::StopCentipedeWalking:
		ConsoleMsg::WriteLine("StopCentipedeWalking triggered");
		pCmd = new CmdStopAudio(Instance().aCentipedeWalking);
		break;
	case AudioEvents::MushroomRegen:
		ConsoleMsg::WriteLine("MushroomRegen noise triggered");
		pCmd = new CmdPlayAudio(Instance().aMushroomRegen);
		break;
	case AudioEvents::FleaFalling:
		ConsoleMsg::WriteLine("FleaFalling noise triggered");
		pCmd = new CmdLoopAudio(Instance().aFleaFalling);
		break;
	case AudioEvents::StopFleaFalling:
		ConsoleMsg::WriteLine("StopFleaFalling triggered");
		pCmd = new CmdStopAudio(Instance().aFleaFalling);
		break;
	case AudioEvents::SpiderWalking:
		ConsoleMsg::WriteLine("SpiderWalking noise triggered");
		pCmd = new CmdLoopAudio(Instance().aSpiderWalking);
		break;
	case AudioEvents::StopSpiderWalking:
		ConsoleMsg::WriteLine("StopSpiderWalking triggered");
		pCmd = new CmdStopAudio(Instance().aSpiderWalking);
		break;
	case AudioEvents::ScorpionWalking:
		ConsoleMsg::WriteLine("ScorpionWalking noise triggered");
		pCmd = new CmdLoopAudio(Instance().aScorpionWalking);
		break;
	case AudioEvents::StopScorpionWalking:
		ConsoleMsg::WriteLine("StopScorpionFalling triggered");
		pCmd = new CmdStopAudio(Instance().aScorpionWalking);
		break;
	default:
		ConsoleMsg::WriteLine("<nothing>");
		break;
	}

	return pCmd;
}

void AudioManager::PlayAudio(sf::Sound* a)
{
	// Play the audio once
	a->play();
}

void AudioManager::LoopAudio(sf::Sound* a)
{
	// Loop the audio
	a->setLoop(true);
	a->play();
}

void AudioManager::StopAudio(sf::Sound* a)
{
	// Stop the audio
	a->stop();
}

void AudioManager::PushAudioCmd(CmdAudio* c)
{
	Instance().StackCmd.push(c);
}

void AudioManager::SendAudioCmd(CmdAudio* c)
{
	Instance().pAudio->Play(c);
}

void AudioManager::ProcessAudio()
{
	Instance().privProcessAudio();
}

void AudioManager::privProcessAudio()
{
//	ConsoleMsg::WriteLine("Processing all sounds commands for this frame:");

	CmdAudio* c;

	while (!StackCmd.empty())
	{
		c = StackCmd.top();
		c->Execute();

		StackCmd.pop(); 
	}
}

void AudioManager::Mute()
{
	Instance().pAudio = Instance().Silent;
}

void AudioManager::Unmute()
{
	Instance().pAudio = Instance().Play;
}

AudioManager::~AudioManager()
{
	ConsoleMsg::WriteLine("deleting audiomanager");
	delete Silent;
	delete Play;
	delete aBulletFired;
	delete aPlayerExplosion;
	delete aEnemyExplosion;
	delete aCentipedeWalking;
	delete aMushroomRegen;
	delete aFleaFalling;
	delete aSpiderWalking;
	delete aScorpionWalking;
	while (!StackCmd.empty())
	{
		StackCmd.pop();
	}
}

void AudioManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}