#ifndef _HUDManager
#define _HUDManager

#include "../TEAL/CommonElements.h"

class ScorePrinter;
class LivesPrinter;
class AttractorDisplay;
class MushroomField;

class HUDManager
{
private:
	static HUDManager *ptrInstance;

	HUDManager();
	HUDManager(const HUDManager&) = delete;
	HUDManager& operator=(const HUDManager&) = delete;
	~HUDManager();

	static HUDManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new HUDManager;
		return *ptrInstance;
	}

	ScorePrinter* pPlayerScore;
	LivesPrinter* pPlayerLives;
	AttractorDisplay* pAttractorDisplay;

	void privUpdateScore(int score);
	void privUpdateLives(int lives);
	void privCreateAttractorHUD(MushroomField* g);
	void privDisplayAttractorHUD();
	void privHideAttractorHUD();
	void privUpdateHighScore(MushroomField* g, int score);

public:
	static void InitializePlayerScore(int score, int lives, sf::Vector2f p);
	static void CreateAttractorHUD(MushroomField* g) { Instance().privCreateAttractorHUD(g); };
	static void DisplayAttractorHUD() { Instance().privDisplayAttractorHUD(); };
	static void HideAttractorHUD() { Instance().privHideAttractorHUD(); };
	static void UpdateScore(int score) { Instance().privUpdateScore(score); };
	static void UpdateLives(int lives) { Instance().privUpdateLives(lives); };
	static void UpdateHighScore(MushroomField* g, int score) { Instance().privUpdateHighScore(g, score); };
	
	static void Terminate();
};

#endif