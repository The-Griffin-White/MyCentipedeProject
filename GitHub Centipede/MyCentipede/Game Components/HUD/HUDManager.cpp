#include "HUDManager.h"

#include "ScorePrinter.h"
#include "LivesPrinter.h"

#include "../Constants.h"

#include "AttractorDisplay.h"

HUDManager* HUDManager::ptrInstance = nullptr;

HUDManager::HUDManager()
{
	pPlayerScore = nullptr;
	pPlayerLives = nullptr;
	pAttractorDisplay = nullptr;
}

HUDManager::~HUDManager()
{
	ConsoleMsg::WriteLine("deleting hudmanager");
}

void HUDManager::InitializePlayerScore(int score, int lives, sf::Vector2f p)
{
	Instance().pPlayerScore = new ScorePrinter(score, p);
	Instance().pPlayerLives = new LivesPrinter(lives, p + sf::Vector2f(CellSizeF, 0));
}

void HUDManager::privUpdateScore(int s)
{
	pPlayerScore->UpdateScore(s);
}

void HUDManager::privUpdateHighScore(MushroomField* g, int score)
{
//	ConsoleMsg::WriteLine("*****************Updating high scores*************");
	pAttractorDisplay->UpdateHighScores(g, score);
}

void HUDManager::privUpdateLives(int l)
{
	pPlayerLives->UpdateLives(l);
}

void HUDManager::privCreateAttractorHUD(MushroomField* g)
{
	pAttractorDisplay = new AttractorDisplay(g);
}

void HUDManager::privDisplayAttractorHUD()
{
	pAttractorDisplay->Show();
}

void HUDManager::privHideAttractorHUD()
{
	pAttractorDisplay->Hide();
}

void HUDManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}