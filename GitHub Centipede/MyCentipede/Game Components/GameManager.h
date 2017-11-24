#ifndef _GameManager
#define _GameManager

class GameCommandProcessor;
class WaveLoader;
class Wave;

class GameManager
{
private:
	static GameManager* ptrInstance;

	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	~GameManager();

	static GameManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new GameManager;
		return *ptrInstance;
	}

	void InitWaves();
	void InitWaveFromFile(int numWave);

	static const int maxNumWaves = 16;
	WaveLoader* waveArray[maxNumWaves];
	int numWavesLoaded;
	void privLoadWave(int wave);
	void privResetWave();
	void privRestartWave();
	void privGoToNextLevel();
	void privRemoveAllCritters();

	void privSpawnFleas();

	Wave* currWave;

	GameCommandProcessor* processor;

public:
	/// Sends our player to the next wave
	static void GoToNextLevel() { Instance().privGoToNextLevel(); };
	/// Loads the wave based on the int given
	static void LoadWave(int wave) { Instance().privLoadWave(wave); };
	/// Deletes the current wave and prepares to either restart or go back to attractor (if out of lives)
	static void ResetWave() { Instance().privResetWave(); };
	/// Restarts the current wave #
	static void RestartWave() { Instance().privRestartWave(); };
	/// Tells the current wave to start spawning fleas (based on command given by mushroomfield)
	static void SpawnFleas() { Instance().privSpawnFleas(); };
	/// Removes critters/bullet from current game field
	static void RemoveAllCritters() { Instance().privRemoveAllCritters(); };
	
	static void Terminate();
};

#endif