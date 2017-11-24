#include "..\Player\PlayerManager.h"
#include "LivesPrinter.h"

#include "GlyphFactory.h"

static const int maxLength = 10;
static const int heightOffset = 8;		// Needed to make sure the text doesn't clip with any passing critters
static const int standardLives = 2;		// We shouldn't call this, but in case I'm testing something...

LivesPrinter::LivesPrinter(int l, sf::Vector2f p)
{
	str = "";
	for (int i = 0; i < l; i++)
		str.append("?");
	str.append(" ");

	rootpos = p;
	nextpos = rootpos;
	nextpos.y -= heightOffset;

	unsigned int itr = 0;
	for (int i = 0; i < MaxNumPlayerLives; i++)
	{
		if (itr < str.length())
		{
			symbols[i] = (myfont.GetGlyph(str.at(itr), nextpos));
			itr++;
		}
		else
		{
			symbols[i] = (myfont.GetGlyph(' ', nextpos));
		}
		nextpos.x += myfont.CellWidth();
	}
}

void LivesPrinter::UpdateLives(int l)
{
	str = "";
	for (int i = 0; i < l; i++)
		str.append("?");
	str.append(" ");

	nextpos = rootpos;
	nextpos.y -= heightOffset;

	ConsoleMsg::WriteLine("Current lives should be " + str);

	unsigned int itr = 0;
	for (int i = 0; i < MaxNumPlayerLives; i++)
	{
		if (itr < str.length())
		{
			if (symbols[i]->ReturnCellID() != str.at(itr))
			{
				GlyphFactory::RecycleGlyph(symbols[i]);
				symbols[i] = (myfont.GetGlyph(str.at(itr), nextpos));
			}
			itr++;
		}
		else
		{
			symbols[i] = (myfont.GetGlyph(' ', nextpos));
		}
		nextpos.x += myfont.CellWidth();
	}
}

void LivesPrinter::Draw()
{
	for (int i = 0; i < MaxNumPlayerLives; i++)
	{
		symbols[i]->Draw();
	}
}