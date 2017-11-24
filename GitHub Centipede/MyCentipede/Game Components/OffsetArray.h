#ifndef _OffsetArray
#define _OffsetArray

struct OffsetArray
{
	float rowoffset;
	float coloffset;

	OffsetArray(float c, float r) : rowoffset(r), coloffset(c) {};
};

#endif