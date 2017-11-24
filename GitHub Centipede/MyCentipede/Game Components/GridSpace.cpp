#include "GridSpace.h"

GridSpace::GridSpace()
{
	pShroom = nullptr;
	type = BlockType::None;
	mushroomHere = Obstacle::Clear;
	playerHere = Obstacle::Clear;
	critterHere = Obstacle::Clear;
}

GridSpace::~GridSpace()
{
	pShroom = nullptr;
}

void GridSpace::SetShroom(Mushroom* s)
{ 
	pShroom = s; 
};
Mushroom* GridSpace::ReturnShroom()
{ 
	return pShroom; 
};

void GridSpace::SetType(BlockType b) 
{ 
	type = b; 
};
BlockType GridSpace::ReturnType() 
{ 
	return type; 
};

void GridSpace::SetMushroomHere(Obstacle t) 
{ 
	mushroomHere = t; 
};
Obstacle GridSpace::ReturnMushroomHere() 
{
	return mushroomHere;
};

void GridSpace::SetPlayerHere(Obstacle t) 
{
	playerHere = t;
};
Obstacle GridSpace::ReturnPlayerHere() 
{ 
	return playerHere; 
};

void GridSpace::SetCritterHere(Obstacle t) 
{ 
	critterHere = t; 
};
Obstacle GridSpace::ReturnCritterHere() 
{ 
	return critterHere; 
};