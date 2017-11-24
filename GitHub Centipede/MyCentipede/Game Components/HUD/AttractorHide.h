#ifndef _AttractorHide
#define _AttractorHide

#include "AttractorDrawStrategy.h"

class AttractorDisplay;

class AttractorHide : public AttractorDrawStrategy
{
public:
	virtual void Draw(AttractorDisplay* ad) override {};
};

#endif