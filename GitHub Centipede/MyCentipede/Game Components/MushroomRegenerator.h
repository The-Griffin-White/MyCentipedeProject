#ifndef _MushroomRegenerator
#define _MushroomRegenerator

#include "TEAL\CommonElements.h"

class Mushroom;

class MushroomRegenerator : public GameObject
{
public:
	MushroomRegenerator();
	
	void Initialize(Mushroom* m);
	
	void Update();
	void Draw() {};
	void Destroy();

private:
	Mushroom* casualty;								// the little guy was wounded in battle
	int itr;
	const int itrCap = 15;							// 60fps, regen 2 mushrooms a second (?), about every 7 frames?
	const int HealAmount = 1;						// no magic numbers, yadayada

};

#endif