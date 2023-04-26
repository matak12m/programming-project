

#include "Player.h"   // include Player header file
#include "SFML/graphics.hpp"
#include "iostream"
#include "Game.h"

// Player function definitions here
void Player::move()   //moves the player in 1 direction, some directions take priority
{
	playerPosition = sprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerPosition.x > 0)  //if left is pressed and character's x position isn't less than 0
	{
		sprite.setPosition(playerPosition.x - speed, playerPosition.y); 
		sprite.setTextureRect(sf::IntRect{ 0,SPRITE_HEIGHT * 3,SPRITE_WIDTH,SPRITE_HEIGHT });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPosition.x < SCREEN_WIDTH-SPRITE_WIDTH)  //if right is pressed and sprite isn't offscreen to the right
	{
		sprite.setPosition(playerPosition.x + speed, playerPosition.y);
		sprite.setTextureRect(sf::IntRect{ 0,SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playerPosition.y > 610) //610 = boundary for the fence
	{ 
		sprite.setPosition(playerPosition.x, playerPosition.y - speed);
		sprite.setTextureRect(sf::IntRect{ 0,0,SPRITE_WIDTH,SPRITE_HEIGHT });
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && playerPosition.y < SCREEN_HEIGHT-SPRITE_HEIGHT) //if downis pressed and sprite isnt under the screen boundary
	{
		sprite.setPosition(playerPosition.x, playerPosition.y + speed);
		sprite.setTextureRect(sf::IntRect{ 0,SPRITE_HEIGHT*2,SPRITE_WIDTH,SPRITE_HEIGHT });
	}
	
}

void Player::takeDamage()
{
	std::cout << "Damage Taken!  \n";
	lives--;
	
}

void Player::dash()
{   

	if (dashRestartClock)
	{
		dashClock.restart();
		dashRestartClock = false;
	}

	timeElapsed = dashClock.getElapsedTime().asSeconds();


	if (timeElapsed < dashTime)
	{
		speed = 10;
	}
	else if (timeElapsed < dashTime * 2.5)
	{
		
		speed = 5;
	}
	else if (timeElapsed = dashTime * 2.5)
	{
		dashRestartClock = true;
		isDashing = false;
	}

}


