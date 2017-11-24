#ifndef _MushroomField
#define _MushroomField

#include "Constants.h"

enum Direction;

class Mushroom;
class CentipedeHead;
class GridSpace;
enum class Obstacle;

class MushroomField
{
public:
	MushroomField();
	~MushroomField();

	/// Sets where mushrooms will spawn, does not create the mushroom objects here
	virtual void InitializeMushrooms();
	/// Subclass for Initialize, sets a mushroom to spawn at this specific coordinate
	void AddMushroomMarkerToGrid(int row, int col);
	/// Spawns mushroom game objects based on the initialization markers
	void SpawnAllMushroomsOnField();
	/// Used to create a new mushroom at row/col. Used by SpawnAllMushroomsOnField
	void RespawnMushroomHere(int row, int col);
	/// Removes mushroom game objects from field (when switching players)
	void RemoveAllMushroomsFromField();
	/// Used to remove the mushroom at row/col. Used by RemoveAllMushroomsFromField
	void RemoveMushroomHere(int row, int col);
	/// Clears the current mushroom field of all markers (so we can re-initialize)
	void ClearMushroomField();
	/// REMOVES this mushroom from the field, does not destroy the game object
	void DeleteMushroom(int row, int col);
	/// Makes mushroom at this point poison. Modifies game object from here
	void MakeMushroomPoison(int row, int col);
	/// Makes mushroom at this point nonpoison. DOES NOT modify game object from here
	void MakeMushroomNonPoison(int row, int col);
	/// Used by spider, calls the mushrooms "MushroomEaten" function
	void EatMushroom(int row, int col);

	/// Actually used by scorpion/spider too. Checks if cell at row/col has a mushroom (and if it is poison)
	Obstacle InspectCentipedeObstacles(int row, int col);
	/// Used by hud. We don't have a block object but this simulates it for centipede collision
	void AddBlockHere(int row, int col);
	/// Add a mushroom at row/col. Does not overlap with existing mushrooms
	void AddMushroomHere(int row, int col);

	/// Modifies fleaThreshold value to change the min number of mushrooms in player area to start flea spawn
	void MushroomsToStartFleaSpawn(int num);
	/// Puts hurt mushrooms in a list to begin regen phase
	void StartMushroomRegen();
	/// Creates a MushroomRegenerator for each hurt shroom until the list is empty
	void RegenMushroom();

	/// Gets the coordinate at the center of the cell at row/col
	static sf::Vector2f GetCenterCoordinate(int row, int col);

	// Unused, would be useful for improved ship/mushroom collision
	static float GetLeftWallCoordinate(int col);
	static float GetRightWallCoordinate(int col);
	static float GetTopWallCoordinate(int row);
	static float GetBottomWallCoordinate(int row);

private:

	GridSpace *MushroomArray[FieldDimensions][FieldDimensions];
	int numMushroomsInPlayerSpace;
	int fleaThreshold;
	std::vector<sf::Vector2i> DamagedShrooms;
};

#endif