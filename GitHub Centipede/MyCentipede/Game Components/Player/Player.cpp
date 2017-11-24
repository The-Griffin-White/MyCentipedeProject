#include "Player.h"
#include "..\MushroomField.h"
#include "..\MushroomFactory.h"
#include "..\Controller.h"
#include "..\GridSpace.h"

#include "..\GameManager.h"
#include "../HUD/HUDManager.h"
#include "../ShipFactory.h"

#include "PlayerOneHUDStrategy.h"
#include "AttractorHUDStrategy.h"

#define MUSHROOMS 1
#define MUSHROOM_GRID 0

/// Takes a Controller (either player or AI) and the mushroomField (replace that later)
Player::Player(Controller* c, MushroomField* g, PlayerHUDStrategy* p)
	: Score(0), scoreTracker(0), Lives(2), Level(1), ShipController(c), Grid(g), scoreUpdater(p)
{
	scoreUpdater->MenuHUD(Grid);
	Grid->InitializeMushrooms();
}

void Player::ResetMushroomField()
{
	Grid->ClearMushroomField();
	Grid->InitializeMushrooms();
}

void Player::InitShip()
{
	ship = ShipFactory::CreateShip();
}

void Player::RemoveShip()
{
	ship->MarkForDestroy();
}

void Player::InitMushroomField()
{
	Grid->SpawnAllMushroomsOnField();
}

void Player::RemoveMushroomField()
{
	ConsoleMsg::WriteLine("Remove all these mushrooms");
	Grid->RemoveAllMushroomsFromField();
}

sf::Vector2f Player::GetShipPos()
{
	return ship->GetPos();
}

/// Returns the current level
int Player::ReturnLevel()
{
	return Level;
}

/// Returns the current Score
int Player::ReturnScore()
{
	return Score;
}

/// Returns current number of lives
int Player::ReturnLives()
{
	return Lives;
}

MushroomField* Player::ReturnGrid()
{
	return Grid;
}

/// Returns center coordinate at the given pos. Maybe replace with MushroomField Static function?
sf::Vector2f Player::GetCenterCoordinate(int row, int col)
{
	return MushroomField::GetCenterCoordinate(row, col);
}

void Player::MushroomsToStartFleaSpawn(int num)
{
	Grid->MushroomsToStartFleaSpawn(num);
}

void Player::RegenMushroomField()
{
	this->Grid->StartMushroomRegen();
}

void Player::RegenNextMushroom()
{
	this->Grid->RegenMushroom();
}

/// Removes a mushroom from the grid
void Player::DeleteMushroom(int row, int col)
{
	this->Grid->DeleteMushroom(row, col);
}

/// Convert MushroomArray cell to contain a poison mushroom
void Player::MakeMushroomPoison(int row, int col)
{
	this->Grid->MakeMushroomPoison(row, col);
}

/// Checks for obstacles that would cause a centipede state change
Obstacle Player::InspectCentipedeObstacles(int row, int col)
{
	return this->Grid->InspectCentipedeObstacles(row, col);
}

/// Rounds vector pos to an x/y index and places a mushroom at that point
void Player::AddMushroomHere(int row, int col)
{
	this->Grid->AddMushroomHere(row, col);
}

void Player::EatMushroom(int row, int col)
{
	this->Grid->EatMushroom(row, col);
}

/// Updates score value
void Player::IncreaseScore(int val)
{
	this->Score += val;
	this->scoreTracker += val;
	if (scoreTracker >= PointsForBonus)
	{
		IncrementLives();
		scoreTracker = 0;
	}
	this->scoreUpdater->UpdateScore(this->Score);
//	ConsoleMsg::WriteLine("Score updated to " + Tools::ToString(Score));
}

void Player::ResetScore()
{
	this->Score = 0;
	this->scoreUpdater->UpdateScore(this->Score);
}

/// Resets the Level back to 1
void Player::ResetLevel()
{
	this->Level = 1;
}

void Player::ResetLives()
{
	this->Lives = 2;
	this->scoreUpdater->UpdateLives(this->Lives);
}

/// Updates to the next level
void Player::IncrementLevel()
{
	this->Level++;
}

void Player::IncrementLives()
{
	if (Lives != 5)
	{
		Lives++;
		this->scoreUpdater->UpdateLives(this->Lives);
	}
}

/// Decrements the current number of lives after the player dies
void Player::DecrementLives()
{
	this->Lives--;
	this->scoreUpdater->UpdateLives(this->Lives);
}


// Ship Control Functions

/// Gets Directions from an arbitrary controller
sf::Vector2f Player::GetPlayerDirections()
{
	return this->ShipController->GetDirections();
}

/// Gets fire control from an arbitrary controller
void Player::GetPlayerFireCommand()
{
	this->ShipController->GetFireControl();
}

void Player::ShootBullet()
{
	this->ship->ShootBullet();
}

Player::~Player()
{
	if (Grid) delete Grid;
	if (scoreUpdater) delete scoreUpdater;
}