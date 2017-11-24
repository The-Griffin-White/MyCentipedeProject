#ifndef _SpiderOffsetArray
#define _SpiderOffsetArray

struct SpiderOffsetArray
{
	float rowoffset;
	float coloffset;

	SpiderOffsetArray(float c, float r) : rowoffset(r), coloffset(c) {};
};

#endif