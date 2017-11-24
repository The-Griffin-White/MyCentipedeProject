#include "AttractorController.h"
#include "Constants.h"

#include "Attractor FSM\AttractorState.h"
#include "Attractor FSM\AttractorMoveFSM.h"
#include "Attractor FSM\AttractorMovementCollection.h"

#include "Player\PlayerManager.h"

AttractorController::AttractorController()
{
	currDirections = sf::Vector2f(0.0f, 0.0f);
	pCurrentState = &AttractorMoveFSM::StateLeftDown;
}

sf::Vector2f AttractorController::GetDirections()
{
//	ConsoleMsg::WriteLine("Using AttractorController");

	currDirections = sf::Vector2f(0.0f, 0.0f);

	currDirections.y += pCurrentState->GetMoveOffsets()->rowoffset;
	currDirections.x += pCurrentState->GetMoveOffsets()->coloffset;

	pCurrentState = pCurrentState->GetNextState();

	return currDirections;
};

void AttractorController::GetFireControl()
{
	PlayerManager::ShootBullet();
}