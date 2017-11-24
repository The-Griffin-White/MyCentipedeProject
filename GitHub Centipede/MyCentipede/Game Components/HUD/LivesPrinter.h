#ifndef _LivesPrinter
#define _LivesPrinter

#include "..\TEAL\CommonElements.h"
#include <list>
#include "AwesomeFont.h"
#include "../Constants.h"

class LivesPrinter : public GameObject
{
public:
	LivesPrinter(int lives, sf::Vector2f pos);
	virtual void UpdateLives(int lives);
	virtual void Draw();

private:
	AwesomeFont myfont; // i choose you

	Glyph* symbols[MaxNumPlayerLives];
	sf::Vector2f rootpos;
	sf::Vector2f nextpos;
	std::string str;
};


#endif