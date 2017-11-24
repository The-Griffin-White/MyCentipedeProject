#include "GlyphFactory.h"

#include "SpriteSheet.h"

GlyphFactory* GlyphFactory::ptrInstance = nullptr;

GlyphFactory::GlyphFactory()
{
}

GlyphFactory::~GlyphFactory()
{
	ConsoleMsg::WriteLine("deleting glyphfactory");
	while (!recycledGlyphs.empty())
	{
		delete recycledGlyphs.top();
		recycledGlyphs.pop();
	}
}

void GlyphFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

Glyph* GlyphFactory::privCreateGlyph(SpriteSheet* sheet, char cellChar, sf::Vector2f pos)
{
	Glyph* b;

	if (recycledGlyphs.empty())
	{
		b = new Glyph;
	}
	else
	{
		b = recycledGlyphs.top();
		recycledGlyphs.pop();
	}
	b->Initialize(sheet, sheet->CharToIndex(cellChar), cellChar, pos);
	return b;
}

void GlyphFactory::privRecycleGlyph(Glyph* b)
{
	recycledGlyphs.push(b);
}