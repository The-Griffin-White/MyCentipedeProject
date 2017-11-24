#include "PlayerController.h"

#include "Constants.h"

#include "Player\PlayerManager.h"

PlayerController::PlayerController()
{
	currDirections = sf::Vector2f(0.0f, 0.0f);

	RegisterInput(InputFlags::KeyPressed); // Recieve single-presses events
}

sf::Vector2f PlayerController::GetDirections() 
{
//	ConsoleMsg::WriteLine("Using PlayerController");

	currDirections = sf::Vector2f(0.0f, 0.0f);
	// Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) currDirections += sf::Vector2f(-Ship_Speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) currDirections += sf::Vector2f(Ship_Speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) currDirections += sf::Vector2f(0, -Ship_Speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) currDirections += sf::Vector2f(0, Ship_Speed);

	return currDirections; 
};
void PlayerController::GetFireControl() 
{
	// Fire bullet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		PlayerManager::ShootBullet();
};

void PlayerController::Destroy()
{
	DeregisterInput();
}
