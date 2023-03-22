

#include "Player.h"   // include Player header file
#include "SFML/graphics.hpp"

// Player function definitions here
void Player::move()   //moves the player in 1 direction, some directions take priority
{
	sf::Vector2f position = sprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && position.x > 0) 
	{
		sprite.setPosition(position.x - speed, position.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && position.x < SCREEN_WIDTH-SPRITE_WIDTH) 
	{
		sprite.setPosition(position.x + speed, position.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position.y > 610) //boundary for the fence
	{ 
		sprite.setPosition(position.x, position.y - speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && position.y < SCREEN_HEIGHT-SPRITE_HEIGHT) 
	{
		sprite.setPosition(position.x, position.y + speed);
	}
}