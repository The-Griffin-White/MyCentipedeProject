#ifndef _PlayerHUDStrategy
#define _PlayerHUDStrategy

class MushroomField;

class PlayerHUDStrategy
{
public:
	virtual void UpdateScore(int val) = 0;
	virtual void UpdateLives(int val) = 0;
	virtual void MenuHUD(MushroomField* g) = 0;

};

#endif