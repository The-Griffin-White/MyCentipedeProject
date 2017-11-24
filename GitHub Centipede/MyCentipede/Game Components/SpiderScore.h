#ifndef _SpiderScore
#define _SpiderScore

#include "TEAL\CommonElements.h"

enum class ScoreNumber
{
	Near,
	Medium,
	Far
};

class SpiderScore : public GameObject
{
public:
	SpiderScore();

	void Initialize(sf::Vector2f p, ScoreNumber n);

	void Update();
	void Draw();

private:
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	int itr;


};

#endif