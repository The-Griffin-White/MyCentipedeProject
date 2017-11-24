#ifndef _AttractorController
#define _AttractorController

#include "Controller.h"

class AttractorState;
class Ship;

class AttractorController : public Controller
{
public:
	AttractorController();
	AttractorController(const AttractorController&) = default;
	AttractorController& operator=(const AttractorController&) = default;
	~AttractorController() = default;

	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

	virtual sf::Vector2f GetDirections() override;
	virtual void GetFireControl() override;

private:
	int iterator;
	const AttractorState* pCurrentState;

};

#endif