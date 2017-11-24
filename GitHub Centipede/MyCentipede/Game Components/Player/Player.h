#ifndef _Player
#define _Player

#include "..\Constants.h"
#include "..\GridSpace.h"

class MushroomField;
class Controller;
class ScorePrinter;
class Ship;
class PlayerHUDStrategy;

class Player
{
public:
	Player(Controller* c, MushroomField* g, PlayerHUDStrategy* p);
	~Player();

	sf::Vector2f GetShipPos();
	int ReturnLevel();
	int ReturnScore();
	int ReturnLives();
	MushroomField* ReturnGrid();

	void InitShip();
	void RemoveShip();
	void ResetMushroomField();
	void InitMushroomField();
	void RemoveMushroomField();
	void IncreaseScore(int val);
	void IncrementLevel();
	void IncrementLives();
	void ResetLevel();
	void ResetLives();
	void ResetScore();
	void DecrementLives();

	// MushroomField Controls
	void MushroomsToStartFleaSpawn(int num);
	sf::Vector2f GetCenterCoordinate(int row, int col);
	void RegenMushroomField();
	void RegenNextMushroom();
	void DeleteMushroom(int row, int col);
	void MakeMushroomPoison(int row, int col);
	Obstacle InspectCentipedeObstacles(int row, int col);
	void AddMushroomHere(int row, int col);
	void EatMushroom(int row, int col);

	// Ship Controls
	sf::Vector2f GetPlayerDirections();
	void GetPlayerFireCommand();
	void ShootBullet();

private:
	int Score;
	int scoreTracker;		// Used for life bonuses
	int Lives;
	int Level;
	Ship* ship;
	Controller* ShipController;
	MushroomField* Grid;
	PlayerHUDStrategy* scoreUpdater;
};

#endif