#ifndef _Controller
#define _Controller

#include "TEAL\CommonElements.h"

class Ship;

class Controller : public GameObject
{
public:
	Controller() { };
	Controller(const Controller&) = default;
	Controller& operator=(const Controller&) = default;
	~Controller() {};

	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};

	virtual sf::Vector2f GetDirections() = 0;
	virtual void GetFireControl() = 0;

protected:
	sf::Vector2f currDirections;

};

#endif