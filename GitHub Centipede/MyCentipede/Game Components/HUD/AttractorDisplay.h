#ifndef _AttractorDisplay
#define _AttractorDisplay

#include "../TEAL/CommonElements.h"
#include <list>
#include "AwesomeFont.h"

#define ATTRACTOR_ARRAY_LENGTH 120

class MushroomField;
class HighScore;
class AttractorDrawStrategy;

class AttractorDisplay : public GameObject
{
public:
	AttractorDisplay(MushroomField* g);
	void MapScoresToArray(MushroomField* g);
	virtual void UpdateHighScores(MushroomField* g, int score);
	virtual void Draw();
	virtual void ActualDraw();

	sf::Vector2f GetGlyphCoordinate(int row, int col);

	void Hide();
	void Show();

private:
	AwesomeFont myfont; // i choose you

	Glyph* AttractorMessages[ATTRACTOR_ARRAY_LENGTH];
	Glyph* AttractorScores[ATTRACTOR_ARRAY_LENGTH];
	std::list<HighScore> highScores;
	int currNumMessageGlyphs;
	int currNumScoreGlyphs;

	AttractorDrawStrategy* pDraw;
	AttractorDrawStrategy* pHide;
	AttractorDrawStrategy* pShow;
	
};

#endif