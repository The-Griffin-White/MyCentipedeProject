#ifndef _GlyphFactory
#define _GlyphFactory

#include "../TEAL/CommonElements.h"

#include <stack>
#include "Glyph.h"

class SpriteSheet;

class GlyphFactory
{
private:
	static GlyphFactory *ptrInstance;

	GlyphFactory();
	GlyphFactory(const GlyphFactory&) = delete;
	GlyphFactory& operator=(const GlyphFactory&) = delete;
	~GlyphFactory();

	static GlyphFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new GlyphFactory;
		return *ptrInstance;
	}

	std::stack<Glyph*> recycledGlyphs;

	Glyph* privCreateGlyph(SpriteSheet* sheet, char cellChar, sf::Vector2f pos);
	void privRecycleGlyph(Glyph* b);

public:
	static Glyph* CreateGlyph(SpriteSheet* sheet, char cellChar, sf::Vector2f pos) { return Instance().privCreateGlyph(sheet, cellChar, pos); };
	static void RecycleGlyph(Glyph* b) { Instance().privRecycleGlyph(b); };

	static void Terminate();
};


#endif