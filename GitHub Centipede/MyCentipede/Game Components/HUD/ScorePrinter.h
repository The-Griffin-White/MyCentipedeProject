#ifndef _ScorePrinter
#define _ScorePrinter

#define SCORE_ARRAY_LENGTH 16

#include "..\TEAL\CommonElements.h"
#include "AwesomeFont.h"

class ScorePrinter : public GameObject
{
public:
	ScorePrinter(int score, sf::Vector2f pos);
	virtual void UpdateScore(int score);
	virtual void Draw();

private:
	AwesomeFont myfont; // i choose you

	Glyph* symbols[SCORE_ARRAY_LENGTH];
	sf::Vector2f rootpos;
	sf::Vector2f nextpos;
	std::string str;
};


#endif