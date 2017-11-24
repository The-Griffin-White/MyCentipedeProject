#include "..\Player\PlayerManager.h"
#include "ScorePrinter.h"

#include "GlyphFactory.h"

static const int maxLength = 10;
static const float heightOffset = 8.0f;		// Needed to make sure the text doesn't clip with any passing critters
static const int standardLives = 2;		// We shouldn't call this, but in case I'm testing something...

ScorePrinter::ScorePrinter(int s, sf::Vector2f p)
{
	if (s < 10)
	{
		str = " 0";
		str.append(Tools::ToString(s));
	}
	else
		str = Tools::ToString(s);

	rootpos = p;
	nextpos = rootpos;
	nextpos.y -= heightOffset;

	unsigned int itr = str.length() - 1;
	for (int i = SCORE_ARRAY_LENGTH - 1; i >= 0; i--)
	{
		if (itr > 0)
		{
			symbols[i] = (myfont.GetGlyph(str.at(itr), nextpos));
			itr--;
		}
		else
		{
			symbols[i] = (myfont.GetGlyph(' ', nextpos));
		}
		nextpos.x -= myfont.CellWidth();
	}
}

void ScorePrinter::UpdateScore(int s)
{
	if (s < 10)
	{
		str = " 0";
		str.append(Tools::ToString(s));
	}
	else
	{
		str = " ";
		str.append(Tools::ToString(s));
	}

	nextpos = rootpos;
	nextpos.y -= heightOffset;

	ConsoleMsg::WriteLine("Current Score line should be " + str);

	unsigned int itr = str.length() - 1;
	for (int i = SCORE_ARRAY_LENGTH - 1; i >= 0; i--)
	{
		if (itr > 0)
		{
			ConsoleMsg::WriteLine(Tools::ToString(str.at(itr)));
			if (str.at(itr) != symbols[i]->ReturnCellID())
			{
	//			ConsoleMsg::WriteLine("Updating [" + Tools::ToString(i) + "] index on scoreprinter");
				GlyphFactory::RecycleGlyph(symbols[i]);
				symbols[i] = (myfont.GetGlyph(str.at(itr), nextpos));
			}
			else
			{
	//			ConsoleMsg::WriteLine("Not updating [" + Tools::ToString(i) + "] index on scoreprinter");
			}
			itr--;
		}
		else
		{
			symbols[i] = (myfont.GetGlyph(' ', nextpos));
		}
		nextpos.x -= myfont.CellWidth();
	}
}

void ScorePrinter::Draw()
{
	for (int i = 0; i < SCORE_ARRAY_LENGTH; i++)
	{
		symbols[i]->Draw();
	}
}