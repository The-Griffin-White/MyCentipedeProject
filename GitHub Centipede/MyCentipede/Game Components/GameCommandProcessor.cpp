#include "GameCommandProcessor.h"

#include "ScoreManager.h"
#include "Audio Manager\AudioManager.h"
#include "Player\PlayerManager.h"

#include "GameStartAttractor.h"
#include "GameQuitToAttractor.h"

GameCommandProcessor::GameCommandProcessor()
{
	switchToPlayer = new GameStartAttractor;
	switchToAttractor = new GameQuitToAttractor;

	switchButton = switchToPlayer;

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
}

GameCommandProcessor::~GameCommandProcessor()
{
	switchButton = nullptr;
	delete switchToPlayer;
	delete switchToAttractor;
}

void GameCommandProcessor::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		switchButton->Switch();
	}

	ScoreManager::ProcessScores();
	AudioManager::ProcessAudio();
}

void GameCommandProcessor::Destroy()
{
	DeregisterInput();
}