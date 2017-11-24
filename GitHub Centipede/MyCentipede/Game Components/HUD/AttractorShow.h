#ifndef _AttractorShow
#define _AttractorShow

#include "AttractorDrawStrategy.h"

class AttractorDisplay;

class AttractorShow : public AttractorDrawStrategy
{
public:
	virtual void Draw(AttractorDisplay* ad) override;
};

#endif