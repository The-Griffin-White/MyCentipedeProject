#include "GameManager.h"

#include "Player\PlayerManager.h"
#include "Wave.h"
#include "WaveLoader.h"
#include "WaveFactory.h"

#include "FleaFactory.h"
#include "ScorpionFactory.h"
#include "SpiderFactory.h"
#include "FSMCentipedeFactory.h"
#include "BulletFactory.h"

#include "GameCommandProcessor.h"

// Maybe replace all this with cstring functions? Do it the easy way for now
#include <iostream>
#include <fstream>
#include <sstream>

#include <assert.h>

GameManager* GameManager::ptrInstance = nullptr;

GameManager::GameManager()
{
	processor = new GameCommandProcessor;

	numWavesLoaded = 0;
	currWave = nullptr;

	InitWaves();
}

GameManager::~GameManager()
{
	ConsoleMsg::WriteLine("deleting gamemanager");
	for (int i = 0; i < maxNumWaves; i++)
	{
		if (waveArray[i]) delete waveArray[i];
	}
	if (currWave) delete currWave;
}

void GameManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

/// Test Initialization of Waves
void GameManager::InitWaves()
{
	waveArray[0] = new WaveLoader;
	numWavesLoaded++;

	for (int i = 1; i < maxNumWaves; i++)
	{
		InitWaveFromFile(i);
		numWavesLoaded++;
	}
}

void GameManager::InitWaveFromFile(int numWave)
{
	bool centipede = waveArray[numWave - 1]->SpawnCentipede();
	bool soloHead = waveArray[numWave - 1]->SpawnSoloHead();
	int numSegments = waveArray[numWave - 1]->NumberSegments();
	bool flea = waveArray[numWave - 1]->SpawnFleas();
	int mushroomsToSpawnFlea = waveArray[numWave - 1]->NumberMushroomsToSpawnFleas();
	int fleaCap = waveArray[numWave - 1]->FleaCapNumber();
	bool scorpion = waveArray[numWave - 1]->SpawnScorpions();
	int scorpionProb = waveArray[numWave - 1]->ScorpionProbabilityNumber();
	int scorpionCap = waveArray[numWave - 1]->ScorpionCapNumber();
	bool spider = waveArray[numWave - 1]->SpawnSpiders();
	int spiderProb = waveArray[numWave - 1]->SpiderProbabilityNumber();
	int spiderCap = waveArray[numWave - 1]->SpiderCapNumber();

	std::string numWaveStr = Tools::ToString(numWave);
	std::string line;
	std::ifstream myfile("wavedata.txt");
	
	if (myfile.is_open())
	{
//		ConsoleMsg::WriteLine("*******Reading from file********");
		while (getline(myfile, line))
		{
//			ConsoleMsg::WriteLine("Reading Line: " + line);
			std::istringstream iss(line);
			std::string word;
			iss >> word;

			// Check if this is our wave
			if (word == "wave")
			{
				iss >> word;
				if (word == numWaveStr)
				{
					while (getline(myfile, line))
					{
//						ConsoleMsg::WriteLine("Reading Line: " + line);
						std::istringstream iss(line);
						std::string word;
						iss >> word;

//						ConsoleMsg::WriteLine("Reading Word: " + word);
						// Big fucking if statement
						if (word == "centipede")
						{
							iss >> word;
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							if (word == "yes")
							{
								centipede = true;
							}
							else
							{
								centipede = false;
							}
						}
						if (word == "solohead")
						{
							iss >> word;
							//							ConsoleMsg::WriteLine("Reading Word: " + word);
							if (word == "yes")
							{
								soloHead = true;
							}
							else
							{
								soloHead = false;
							}
						}
						if (word == "numsegments")
						{
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> numSegments;
						}
						if (word == "flea")
						{
							iss >> word;
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							if (word == "yes")
							{
								flea = true;
							}
							else
							{
								flea = false;
							}
						}
						if (word == "mushroomstospawnflea")
						{
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> mushroomsToSpawnFlea;
						}
						if (word == "fleacap")
						{
							//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> fleaCap;
						}
						if (word == "scorpion")
						{
							iss >> word;
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							if (word == "yes")
							{
								scorpion = true;
							}
							else
							{
								scorpion = false;
							}
						}
						if (word == "scorpionprob")
						{
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> scorpionProb;
						}
						if (word == "scorpioncap")
						{
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> scorpionCap;
						}
						if (word == "spider")
						{
							iss >> word;
//							ConsoleMsg::WriteLine("Reading Word: " + word);
							if (word == "yes")
							{
								spider = true;
							}
							else
							{
								spider = false;
							}
						}
						if (word == "spiderprob")
						{
							//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> spiderProb;
						}
						if (word == "spidercap")
						{
							//							ConsoleMsg::WriteLine("Reading Word: " + word);
							iss >> spiderCap;
						}
						if (word == "}")
						{
							break;
						}
					}
					break;
				}
			}			
		}
		myfile.close();
	}
	else
	{
		ConsoleMsg::ShowError("***************Didn't get our file*********************");
		assert(0);
	}

	waveArray[numWave] = new WaveLoader(centipede, soloHead, numSegments,
										flea, mushroomsToSpawnFlea, fleaCap, 
										scorpion, scorpionProb, scorpionCap, 
										spider, spiderProb, spiderCap);
}

void GameManager::privLoadWave(int w)
{
	if (currWave)
	{
		WaveFactory::RecycleWave(currWave);
		currWave = nullptr;
	}

	int waveNum = w;
	if (waveNum > numWavesLoaded)
	{
		waveNum = numWavesLoaded;
	}

	currWave = WaveFactory::CreateWave(waveArray[waveNum]);
}

void GameManager::privResetWave()
{
	privRemoveAllCritters();

	if (currWave)
	{
		WaveFactory::RecycleWave(currWave);
		currWave = nullptr;
	}

	if (PlayerManager::OutOfLives())
	{
//		PlayerManager::ResetLevel();
//		PlayerManager::ResetLives();
		PlayerManager::SwitchToAttractor();
	}

	PlayerManager::DecrementLives();
	PlayerManager::RegenMushroomField();
}

void GameManager::privRemoveAllCritters()
{
	FleaFactory::RecallFleas();
	ScorpionFactory::RecallScorpions();
	SpiderFactory::RecallSpiders();
	FSMCentipedeFactory::RecallCentipedes();
	BulletFactory::RecallBullets();
}

void GameManager::privRestartWave()
{
	PlayerManager::ReloadLevel();
	PlayerManager::RespawnShip();
}

void GameManager::privGoToNextLevel()
{
	PlayerManager::GoToNextLevel();
}

void GameManager::privSpawnFleas()
{
	currWave->StartFleaSpawn();
}