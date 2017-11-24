#include "SpiderScore.h"

#include "Constants.h"

static const float offset = CellSizeF;			// We don't want it right on top of the explosion when the spider dies

SpiderScore::SpiderScore()
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("SpiderScore"), 1, 3);
	MainSprite.setScale(DoubleScale, DoubleScale);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
}

void SpiderScore::Initialize(sf::Vector2f p, ScoreNumber n)
{
	itr = 0;
	p.y -= offset;
	MainSprite.setPosition(p);
	if (n == ScoreNumber::Near)
	{
		MainSprite.SetAnimation(2, 2, false);
	}
	else if (n == ScoreNumber::Medium)
	{
		MainSprite.SetAnimation(1, 1, false);
	}
	else
	{
		MainSprite.SetAnimation(0, 0, false);
	}
}

void SpiderScore::Update()
{
	if (itr >= SpiderScore_Display_Length)
	{
		MarkForDestroy();
	}
	itr++;
	MainSprite.Update();
}

void SpiderScore::Draw()
{
	WindowManager::MainWindow.draw(MainSprite);
}