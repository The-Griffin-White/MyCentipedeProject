#include "MushroomField.h"
#include "MushroomFactory.h"
#include "FleaFactory.h"
#include "ScorpionFactory.h"
#include "SpiderFactory.h"
#include "GridSpace.h"

#include "FSMCentipedeHead.h"
#include "FSMCentipedeBody.h"
#include "FSMCentipedeFactory.h"

#include "GameManager.h"

#include "MushroomRegeneratorFactory.h"

#define MUSHROOMS 1
#define MUSHROOM_GRID 0


/// Construct this shit
MushroomField::MushroomField()
{
	for (int row = 0; row < FieldDimensions; row++)
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			MushroomArray[row][col] = new GridSpace;
		}
	}
	numMushroomsInPlayerSpace = 0;
	fleaThreshold = 1;
}

MushroomField::~MushroomField()
{
	for (int row = 0; row < FieldDimensions; row++)
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			delete MushroomArray[row][col];
		}
	}
}

/// Creates our base array of mushrooms
void MushroomField::InitializeMushrooms()
{	
#if MUSHROOMS
#if MUSHROOM_GRID
	for (int row = 0; row < MaxCell; row++)
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			if (row % 2 == 0 && col % 2 != 0 && MushroomArray[row][col]->ReturnMushroomHere() == Obstacle::Clear)
			{
				AddMushroomMarkerToGrid(row, col);
				if (row >= TopPlayerRow)
					numMushroomsInPlayerSpace++;
			}
			else if (row % 2 != 0 && col % 2 == 0 && MushroomArray[row][col]->ReturnMushroomHere() == Obstacle::Clear)
			{
				AddMushroomMarkerToGrid(row, col);
				if (row >= TopPlayerRow)
					numMushroomsInPlayerSpace++;
			}
		}
	}
#else
	int count;
	int probability;
	for (int row = 0; row < MaxCell; row++)
	{
		count = 0;
		for (int col = 0; col < FieldDimensions; col++)
		{
			if ((row != MinCell && col != Centipede_Spawn_Col) || (row != Ship_Start_Row && col != Ship_Start_Col))
			{
				probability = rand() % MushroomField_Likelihood_of_Spawn;
				if (probability == 1 && MushroomArray[row][col]->ReturnMushroomHere() == Obstacle::Clear)
				{
					count++;
					AddMushroomMarkerToGrid(row, col);
					if (row >= TopPlayerRow)
						numMushroomsInPlayerSpace++;
				}
				if (row < FieldDimensions - PlayerField && count == MaxMushroomsInEnemyRow) break;
				else if (row >= FieldDimensions - PlayerField && count == MaxMushroomsInPlayerRow) break;
			}
		}
	}
	ConsoleMsg::WriteLine("Number of Shrooms in Player Space = " + Tools::ToString(numMushroomsInPlayerSpace));
#endif
#endif
}

void MushroomField::AddMushroomMarkerToGrid(int row, int col)
{
	MushroomArray[row][col]->SetMushroomHere(Obstacle::Blocked);
	MushroomArray[row][col]->SetType(BlockType::Mushroom);
}

void MushroomField::SpawnAllMushroomsOnField()
{
	for (int row = 0; row < MaxCell; row++)
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			if (MushroomArray[row][col]->ReturnMushroomHere() != Obstacle::Clear &&
				MushroomArray[row][col]->ReturnType() == BlockType::Mushroom)
			{
				RespawnMushroomHere(row, col);
			}
		}
	}
}

void MushroomField::RespawnMushroomHere(int row, int col)
{
	MushroomArray[row][col]->SetShroom(MushroomFactory::CreateMushroom(GetCenterCoordinate(row, col), this, row, col));
}

void MushroomField::RemoveAllMushroomsFromField()
{
	for (int row = 0; row < MaxCell; row++)
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			if (MushroomArray[row][col]->ReturnShroom())
			{
				ConsoleMsg::WriteLine("Removing this mushroom in particular");
				RemoveMushroomHere(row, col);
			}
		}
	}
}

void MushroomField::RemoveMushroomHere(int row, int col)
{
	MushroomArray[row][col]->ReturnShroom()->MarkForDestroy();
	MushroomArray[row][col]->SetShroom(nullptr);
}

void MushroomField::ClearMushroomField()
{
	for (int row = 0; row < FieldDimensions; row++)
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			if ( MushroomArray[row][col]->ReturnShroom() ) MushroomArray[row][col]->ReturnShroom()->MarkForDestroy();
			MushroomArray[row][col] = new GridSpace;
		}
	}
	numMushroomsInPlayerSpace = 0;
}

void MushroomField::EatMushroom(int row, int col)
{
	if (MushroomArray[row][col]->ReturnShroom())
		MushroomArray[row][col]->ReturnShroom()->MushroomEaten();
}

/// Removes a mushroom from the grid
void MushroomField::DeleteMushroom(int row, int col)
{
//	ConsoleMsg::WriteLine("Mushroom cleared from Field");
	MushroomArray[row][col]->SetShroom(nullptr);
	MushroomArray[row][col]->SetMushroomHere(Obstacle::Clear);
	if (row >= TopPlayerRow)
		numMushroomsInPlayerSpace--;
	ConsoleMsg::WriteLine("Number of Shrooms in Player Space = " + Tools::ToString(numMushroomsInPlayerSpace));
	if (row >= TopPlayerRow && numMushroomsInPlayerSpace <= fleaThreshold)
	{
		ConsoleMsg::WriteLine("**********Spawning Fleas**********");
		GameManager::SpawnFleas();
	}
}

void MushroomField::MushroomsToStartFleaSpawn(int num)
{
	fleaThreshold = num;
}

void MushroomField::MakeMushroomPoison(int row, int col)
{
	if (MushroomArray[row][col]->ReturnShroom())
	{
		MushroomArray[row][col]->ReturnShroom()->MakePoison();
		MushroomArray[row][col]->SetMushroomHere(Obstacle::Poison);
	}
}

void MushroomField::MakeMushroomNonPoison(int row, int col)
{
	if (MushroomArray[row][col]->ReturnType() == BlockType::Mushroom)
	{
		MushroomArray[row][col]->SetMushroomHere(Obstacle::Blocked);
	}
}

void MushroomField::StartMushroomRegen()
{
	ConsoleMsg::WriteLine("*******We are in the Regen Function*******");
	// add hurt mushrooms to a list
	for (int row = 0; row < FieldDimensions - 2; row++)			// iterate from the bottom up
	{
		for (int col = 0; col < FieldDimensions; col++)
		{
			if (MushroomArray[row][col]->ReturnShroom())
			{
				ConsoleMsg::WriteLine("*******We have a Mushroom*******");
				MushroomArray[row][col]->ReturnShroom()->MakeNonPoison();
				if (MushroomArray[row][col]->ReturnShroom()->IsMushroomHurt())
				{
					ConsoleMsg::WriteLine("*******We have a hurt Mushroom*******");
					DamagedShrooms.push_back(sf::Vector2i(row, col));
				}
			}
		}
	}

	RegenMushroom();
}

void MushroomField::RegenMushroom()
{
	if (DamagedShrooms.empty())
	{
		GameManager::RestartWave();
	}
	else
	{
		// Normally x and y do not correlate to row and col, but this ordering matches my normal notation and x and y are not used elsewhere, so hopefully no confusion...
		int row = DamagedShrooms.back().x;
		int col = DamagedShrooms.back().y;

		// Block types don't get hurt, so forcing this cast is ok for now
		MushroomRegeneratorFactory::CreateMushroomRegenerator((Mushroom*)MushroomArray[row][col]->ReturnShroom());

		DamagedShrooms.pop_back();
	}
}

/// Checks for obstacles that would cause a centipede state change
Obstacle MushroomField::InspectCentipedeObstacles(int row, int col)

{
	if (row > MaxCell || row < MinCell || col < MinCell || col > MaxCell)
	{
		return Obstacle::Blocked;
	}
	else if (MushroomArray[row][col]->ReturnMushroomHere() == Obstacle::Blocked)
	{
		return Obstacle::Blocked;
	}
	else if (MushroomArray[row][col]->ReturnMushroomHere() == Obstacle::Poison)
	{
		return Obstacle::Poison;
	}
	else // Nothing in this space blocking centipede movement
	{
		return Obstacle::Clear;
	}
}

void MushroomField::AddBlockHere(int row, int col)
{
	if ((col >= MinCell && col <= MaxCell) && (row >= MinCell || row < Mushroom_MaxCell))
	{
		if (MushroomArray[row][col]->ReturnShroom() == nullptr)
		{
//			ConsoleMsg::WriteLine("Adding a block at X =" + Tools::ToString(x) + " Y = " + Tools::ToString(y));
			MushroomArray[row][col]->SetType(BlockType::Block);
			MushroomArray[row][col]->SetMushroomHere(Obstacle::Blocked);
		}
	}
}

/// Places a mushroom at coordinates x / y
void MushroomField::AddMushroomHere(int row, int col)
{
	if ((col >= MinCell && col <= MaxCell) && (row >= MinCell || row < Mushroom_MaxCell))
	{
		if (MushroomArray[row][col]->ReturnMushroomHere() == Obstacle::Clear)
		{
//			ConsoleMsg::WriteLine("Adding a mushroom at X =" + Tools::ToString(x) + " Y = " + Tools::ToString(y));
			MushroomArray[row][col]->SetShroom(MushroomFactory::CreateMushroom(GetCenterCoordinate(row, col), this, row, col));
			AddMushroomMarkerToGrid(row, col);
			if (row >= TopPlayerRow)
				numMushroomsInPlayerSpace++;
		}
	}
}

/// Returns window coordinates of the center of a grid space
sf::Vector2f MushroomField::GetCenterCoordinate(int row, int col)
{
	return sf::Vector2f(col * CellSizeF + CellSize_HalfF, row * CellSizeF + CellSize_HalfF + CellSizeF);
}
/// Returns window coordinate of the left-side of a grid column
float MushroomField::GetLeftWallCoordinate(int col)
{
	return float(col * CellSize);
}
/// Returns window coordinate of the right-side of a grid column
float MushroomField::GetRightWallCoordinate(int col)
{
	return float(col * CellSize + CellSize);
}
/// Returns window coordinate of the top-side of a grid row
float MushroomField::GetTopWallCoordinate(int row)
{
	return float(row * CellSize);
}
/// Returns window coordinate of the bottom-side of a grid row
float MushroomField::GetBottomWallCoordinate(int row)
{
	return float(row * CellSize + CellSize);
}