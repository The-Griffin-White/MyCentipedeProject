#ifndef _PlayerOneHUDStrategy
#define _PlayerOneHUDStrategy

#include "PlayerHUDStrategy.h"

class PlayerOneHUDStrategy : public PlayerHUDStrategy
{
public:
	virtual void UpdateScore(int val) override;
	virtual void UpdateLives(int val) override;
	virtual void MenuHUD(MushroomField* g) override {};
};

#endif