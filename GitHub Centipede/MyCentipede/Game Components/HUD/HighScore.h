#ifndef _HighScore
#define _HighScore

#include "../TEAL/CommonElements.h"

#define NAME_LENGTH 4

class HighScore
{
public:
	HighScore(int s, std::string n)
	{
		score = s;
		name = n;
	}

	int Score() { return score; };
	std::string Name() { return name; };

private:
	int score;
	std::string name;

};

#endif