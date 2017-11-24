#ifndef _AttractorState
#define _AttractorState

// Abstract Spider State class

struct AttractorOffsetArray;

class AttractorState
{
public:
	AttractorState() {};

	const AttractorOffsetArray* GetMoveOffsets() const { return pMoveOffsets; }
	virtual const AttractorState* GetNextState() const = 0;

protected:
	const AttractorOffsetArray* pMoveOffsets;
};

#endif