#include "AttractorDisplay.h"

#include "GlyphFactory.h"

#include "../Player/PlayerManager.h"
#include "../MushroomField.h"

#include "AttractorHide.h"
#include "AttractorShow.h"

#include "HighScore.h"

static const float heightOffset = 8.0f;
static const float widthOffset = 6.0f;
static const int numHighScores = 8;

AttractorDisplay::AttractorDisplay(MushroomField* g)
{
	pHide = new AttractorHide;
	pShow = new AttractorShow;
	pDraw = pShow;

//	Hard code some default scores...
	highScores.push_front( HighScore(100, "nun") );
	highScores.push_front( HighScore(12201, "kdr") );
	highScores.push_front( HighScore(12805, "ed"));
	highScores.push_front( HighScore(13010, "atr"));
	highScores.push_front( HighScore(13210, "dre"));
	highScores.push_front( HighScore(14320, "l4z"));
	highScores.push_front( HighScore(15432, "grt"));
	highScores.push_front( HighScore(16543, "vrx"));
	
	currNumMessageGlyphs = 0;
	currNumScoreGlyphs = 0;

	MapScoresToArray(g);

	sf::Vector2f p;
	int itr = 0;
	int row = 1;
	int col = 11;

	std::string scoresDisplay = "high scores";
	for (unsigned int i = 0; i < scoresDisplay.length(); i++)
	{
		g->AddBlockHere(row, col + i);
		p = GetGlyphCoordinate(row, col + i);
		AttractorMessages[itr] = (myfont.GetGlyph(scoresDisplay.at(i), p));
		currNumMessageGlyphs++;
		itr++;
	}

	std::string startCommand = "backspace to play";
	row = 12;
	col = 8;
	for (unsigned int i = 0; i < startCommand.length(); i++)
	{
		g->AddBlockHere(row, col + i);
		p = GetGlyphCoordinate(row, col + i);
		AttractorMessages[itr] = (myfont.GetGlyph(startCommand.at(i), p));
		currNumMessageGlyphs++;
		itr++;
	}

	std::string bonusLine = "bonus every ";
	bonusLine.append(Tools::ToString(PointsForBonus));
	row = 13;
	col = 8;
	for (unsigned int i = 0; i < bonusLine.length(); i++)
	{
		g->AddBlockHere(row, col + i);
		p = GetGlyphCoordinate(row, col + i);
		AttractorMessages[itr] = (myfont.GetGlyph(bonusLine.at(i), p));
		currNumMessageGlyphs++;
		itr++;
	}

	std::string copyright = "[2017";
	row = 32;
	col = 12;
	for (unsigned int i = 0; i < copyright.length(); i++)
	{
		p = GetGlyphCoordinate(row, col + i);
		AttractorMessages[itr] = (myfont.GetGlyph(copyright.at(i), p));
		currNumMessageGlyphs++;
		itr++;
	}
}

void AttractorDisplay::MapScoresToArray(MushroomField* g)
{
	currNumScoreGlyphs = 0;

	int itr = 0;
	int row = -1;
	int col = 14;
	sf::Vector2f p;
	std::string highestScore = Tools::ToString(highScores.front().Score());
	for (unsigned int i = 0; i < highestScore.length(); i++)
	{
		p = GetGlyphCoordinate(row, col + i);
		AttractorScores[itr] = (myfont.GetGlyph(highestScore.at(i), p));
		currNumScoreGlyphs++;
		itr++;
	}


	// Displaying the various scores
	row = 2;
	col = 11;
	for (std::list<HighScore>::iterator iterator = highScores.begin(), end = highScores.end(); iterator != end; ++iterator)
	{
		int score = (*iterator).Score();
		std::string sc = Tools::ToString(score);
		for (unsigned int i = 0; i < sc.length(); i++)
		{
			g->AddBlockHere(row, col + i);
			p = GetGlyphCoordinate(row, col + i);
			AttractorScores[itr] = (myfont.GetGlyph(sc.at(i), p));
			currNumScoreGlyphs++;
			itr++;
		}
		col = 18;
		for (unsigned int i = 0; i < (*iterator).Name().length(); i++)
		{
			g->AddBlockHere(row, col + i);
			p = GetGlyphCoordinate(row, col + i);
			AttractorScores[itr] = (myfont.GetGlyph((*iterator).Name().at(i), p));
			currNumScoreGlyphs++;
			itr++;
		}
		row++;
		col = 11;
	}
}

void AttractorDisplay::UpdateHighScores(MushroomField* g, int score)
{
	ConsoleMsg::WriteLine("Updating high scores");
	for (std::list<HighScore>::iterator itr = highScores.begin(), end = highScores.end(); itr != end; ++itr)
	{
		if (score >= (*itr).Score() )
		{
			ConsoleMsg::WriteLine("found a score to replace");
			highScores.insert(itr, HighScore(score, "pl1"));
			highScores.pop_back();
			MapScoresToArray(g);
			break;
		}
	}
}

void AttractorDisplay::Draw()
{
	pDraw->Draw(this);
}

void AttractorDisplay::ActualDraw()
{
	int i = 0;
	int j = 0;
	while (i < currNumMessageGlyphs || j < currNumScoreGlyphs)
	{
		if (j < currNumScoreGlyphs)
		{
			AttractorScores[j]->Draw();
			j++;
		}
		if (i < currNumMessageGlyphs)
		{
			AttractorMessages[i]->Draw();
			i++;
		}
	}
}

sf::Vector2f AttractorDisplay::GetGlyphCoordinate(int row, int col)
{
	return PlayerManager::GetCenterCoordinate(row, col) - sf::Vector2f(widthOffset, heightOffset);
}

void AttractorDisplay::Hide()
{
	pDraw = pHide;
}

void AttractorDisplay::Show()
{
	pDraw = pShow;
}