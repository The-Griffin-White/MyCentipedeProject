#ifndef _PlayerController
#define _PlayerController

#include "Controller.h"

class Ship;

class PlayerController : public Controller
{
public:
	PlayerController();
	PlayerController(const PlayerController&) = default;
	PlayerController& operator=(const PlayerController&) = default;
	~PlayerController() = default; 
	
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy();

	virtual sf::Vector2f GetDirections() override;
	virtual void GetFireControl() override;

private:


};

#endif