#ifndef _GridSpace
#define _GridSpace

class Mushroom;

enum class Obstacle
{
	Clear,
	Blocked,
	Poison
};

enum class BlockType
{
	None,
	Block,
	Mushroom
};

class GridSpace
{
public:
	GridSpace();
	GridSpace(const GridSpace&) = default;
	GridSpace& operator=(const GridSpace&) = default;
	~GridSpace();

	void SetShroom(Mushroom* s);
	Mushroom* ReturnShroom();

	void SetType(BlockType b);
	BlockType ReturnType();

	void SetMushroomHere(Obstacle t);
	Obstacle ReturnMushroomHere();

	void SetPlayerHere(Obstacle t);
	Obstacle ReturnPlayerHere();

	void SetCritterHere(Obstacle t);
	Obstacle ReturnCritterHere();


private:
	Mushroom* pShroom;
	BlockType type;
	Obstacle mushroomHere;
	Obstacle playerHere;
	Obstacle critterHere;
};

#endif