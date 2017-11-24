#ifndef _AudioManager
#define _AudioManager

#include <stack>

#include "..\TEAL\CommonElements.h"

class CmdAudio;
class PlayAudioStrategy;

class AudioManager
{
private:
	AudioManager();
	~AudioManager();

	static AudioManager* ptrInstance;

	static AudioManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new AudioManager;
		return *ptrInstance;
	};

	void privProcessAudio();

	// Score values;
	sf::Sound* aBulletFired;
	sf::Sound* aPlayerExplosion;
	sf::Sound* aEnemyExplosion;
	sf::Sound* aCentipedeWalking;
	sf::Sound* aMushroomRegen;
	sf::Sound* aFleaFalling;
	sf::Sound* aSpiderWalking;
	sf::Sound* aScorpionWalking;

	std::stack<CmdAudio*> StackCmd;

	PlayAudioStrategy* Silent;
	PlayAudioStrategy* Play;
	PlayAudioStrategy* pAudio;

public :
	// events
	enum class AudioEvents { BulletFired, PlayerExplosion, EnemyExplosion, 
							CentipedeWalking, StopCentipedeWalking, MushroomRegen,
							FleaFalling, StopFleaFalling, SpiderWalking, StopSpiderWalking, 
							ScorpionWalking, StopScorpionWalking };
	
	static void PlayAudio(sf::Sound* a);
	static void LoopAudio(sf::Sound* a);
	static void StopAudio(sf::Sound* a);
	
	static CmdAudio* GetAudioCommand(AudioEvents ev);

	static void PushAudioCmd(CmdAudio* c);
	static void SendAudioCmd(CmdAudio* c);
	static void ProcessAudio();
	
	static void Mute();
	static void Unmute();
	static void Terminate();
};

#endif