#ifndef _AttractorOffsetArray
#define _AttractorOffsetArray

struct AttractorOffsetArray
{
	float rowoffset;
	float coloffset;

	AttractorOffsetArray(float c, float r) : rowoffset(r), coloffset(c) {};
};

#endif