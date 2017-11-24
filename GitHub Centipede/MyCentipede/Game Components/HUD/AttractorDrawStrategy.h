#ifndef _AttractorDrawStrategy
#define _AttractorDrawStrategy

class AttractorDisplay;

class AttractorDrawStrategy
{
public:
	virtual void Draw(AttractorDisplay* ad) = 0;
};

#endif