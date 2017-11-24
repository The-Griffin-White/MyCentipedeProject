// Glyph
// Andre Berthiaume, May 2013

#include "Glyph.h"
#include "SpriteSheet.h"
#include "..\TEAL\ResourceManager.h"

Glyph::Glyph()
{
	cellId = '`';					// Something that isn't present in our spritesheets...
	sprsheet = 0;
	cellIndex = 0; 
	position = sf::Vector2f(0,0);
}

void Glyph::Initialize(SpriteSheet* sheet, int cellInd, char cellChar, sf::Vector2f pos)
{
	cellId = cellChar;
	sprsheet = sheet;
	position = pos;
	cellIndex = cellInd;
}

void Glyph::Draw()
{
	sprsheet->Draw(cellIndex, position);
}

char Glyph::ReturnCellID()
{
	return cellId;
}