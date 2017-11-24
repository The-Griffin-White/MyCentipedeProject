#ifndef _GameCommandProcessor
#define _GameCommandProcessor

#include "TEAL\/CommonElements.h"

class GameStartStrategy;

class GameCommandProcessor : public GameObject
{
public:
	GameCommandProcessor();
	~GameCommandProcessor();

	void Update();
	void Draw() {};
	void Destroy();

private:
	GameStartStrategy* switchButton;
	GameStartStrategy* switchToPlayer;
	GameStartStrategy* switchToAttractor;
};

#endif