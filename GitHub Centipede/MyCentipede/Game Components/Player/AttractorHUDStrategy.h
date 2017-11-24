#ifndef _AttractorHUDStrategy
#define _AttractorHUDStrategy

#include "PlayerHUDStrategy.h"

class AttractorHUDStrategy : public PlayerHUDStrategy
{
public:
	virtual void UpdateScore(int val) override {};
	virtual void UpdateLives(int val) override {};
	virtual void MenuHUD(MushroomField* g) override;
};

#endif