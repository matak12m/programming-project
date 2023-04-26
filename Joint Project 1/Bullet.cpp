#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <array>

void Bullet::move(bool t_goingUp) //movement of the bullet.
{
	if (t_goingUp)
	{
		spriteRow = 2;
		sprite.setTextureRect(sf::IntRect{ 0, spriteRow * SPRITE_HEIGHT, SPRITE_WIDTH,SPRITE_HEIGHT });
		sprite.setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);

		bulletPosition.y -= speed;
		sprite.setPosition(bulletPosition);
	}
	else
	{
		
		spriteRow = 6;
		sprite.setTextureRect(sf::IntRect{ 0, spriteRow * SPRITE_HEIGHT, SPRITE_WIDTH,SPRITE_HEIGHT });
		sprite.setOrigin(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);

		bulletPosition.y += speed;
		sprite.setPosition(bulletPosition);
	}


}

bool Bullet::detectHit() //detects collision, if it returns true, it triggers a score increase or a loss of life.
{
	sf::Vector2f enemyCollisionPos;
	for (int i = 0; i < Game::enemies.size(); i++) //if bullet hits one of the enemies in the array
	{
		EnemyTwo& enemy = Game::enemies[i]; //reference to the 
		enemyCollisionPos = enemy.enemy2Sprite.getPosition();
		if (bulletPosition.x - enemyCollisionPos.x <COLLISION_SIZE && bulletPosition.y - enemyCollisionPos.y <COLLISION_SIZE && bulletPosition.x - enemyCollisionPos.x > -COLLISION_SIZE && bulletPosition.y - enemyCollisionPos.y > -COLLISION_SIZE)
		{
			enemy.isAlive = false;
			enemy.death();
			Game::playerBullet.canMove = false;

			bulletPosition = { 100, 100 };
			sprite.setPosition(bulletPosition);
			return true;
		}
	}

	enemyCollisionPos = Game::floater.enemySprite.getPosition(); //if bullet hits enemyOne
	if (bulletPosition.x - enemyCollisionPos.x < COLLISION_SIZE && bulletPosition.y - enemyCollisionPos.y < COLLISION_SIZE && bulletPosition.x - enemyCollisionPos.x > -COLLISION_SIZE && bulletPosition.y - enemyCollisionPos.y > -COLLISION_SIZE)
	{
		Game::floater.isAlive = false;
		Game::floater.death();

		Game::playerBullet.canMove = false;

		bulletPosition = { 100, 100 };
		sprite.setPosition(bulletPosition);
		return true;
	}

	if (bulletPosition.y < 0)  // if bullet goes off screen
	{
		bulletPosition = { 100, 100 };
		sprite.setPosition(bulletPosition);
		Game::playerBullet.canMove = false;
		
	}
	return false;
}

bool Bullet::detectHitOnPlayer()
{

	if (bulletPosition.x - Game::myPlayer.playerPosition.x < COLLISION_SIZE && bulletPosition.y - Game::myPlayer.playerPosition.y < COLLISION_SIZE && bulletPosition.x - Game::myPlayer.playerPosition.x > -COLLISION_SIZE && bulletPosition.y - Game::myPlayer.playerPosition.y > -COLLISION_SIZE)
	{
		std::cout << this << std::endl;
		
		death();
		return true;
	}
	if (bulletPosition.y > 800)  // if bullet goes off screen
	{
		death();

	}

	return false;
}


void Bullet::spawn(int t_shooterIndex)  //spawns the appropriate bullet
{
	if (t_shooterIndex == PLAYER_INDEX)
	{
		bulletPosition = Game::myPlayer.playerPosition;
	}
	else if (t_shooterIndex == FLOATER_INDEX)
	{
		bulletPosition = Game::floater.enemyPosition;
	}
	else if (t_shooterIndex >=0 && t_shooterIndex<8)
	{
		bulletPosition = Game::enemies[t_shooterIndex].enemy2Position;
	}
	else
	{
		std::cout << "ghost bullet!";
	}
}

void Bullet::death()
{
	canMove = false;
	bulletPosition = { -200, -200 };
	sprite.setPosition(bulletPosition);

}
