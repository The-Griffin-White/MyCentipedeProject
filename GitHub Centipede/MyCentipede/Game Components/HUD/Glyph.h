// Glyph
// Andre Berthiaume, May 2013

#ifndef _Glyph
#define _Glyph

#include "SFML\Graphics.hpp"

class SpriteSheet; // forward declaration

class Glyph
{
private:
	SpriteSheet* sprsheet;
	int cellIndex;
	char cellId;
	sf::Vector2f position;

public:
	Glyph();
	void Initialize(SpriteSheet* sheet, int cellInd, char cellChar, sf::Vector2f pos);
	void Draw();

	char ReturnCellID();
};


#endif _Glyph