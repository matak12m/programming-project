#include "EnemyOne.h"   // include enemy header file
#include "SFML/graphics.hpp"
#include "Game.h"


void EnemyOne::startMove() //movement down

{

	if (generateRandom)
	{

		srand(time(0));
		generateRandom = false;

		enemyPosition.x = rand() % 1100 + 200;
		enemySprite.setPosition(enemyPosition);
		moveToY = rand() % 200 + 100;


	}
	if (enemyPosition.y < moveToY)
	{
		enemyPosition.y += speed;
		enemySprite.setPosition(enemyPosition);
	}
	else
	{
		isAtGoalY = true;
	}
}
void EnemyOne::move() //movement follos player
{
	sf::Vector2f playerPos = Game::myPlayer.sprite.getPosition();


	if (enemyPosition.x - playerPos.x > -SHOOT_RANGE && enemyPosition.x - playerPos.x < SHOOT_RANGE)
	{
		 //do nothing stop vibrating
	}
	else if (enemyPosition.x > playerPos.x)
	{
		enemyPosition.x -= speed;
		enemySprite.setPosition(enemyPosition);
	}
	else if (enemyPosition.x < playerPos.x)
	{
		enemyPosition.x += speed;
		enemySprite.setPosition(enemyPosition);
	}
	



}

void EnemyOne::death() //dissapear off the screen.
{

	srand(time(0));
	xPos = rand() % 1200 + 150;

	isAlive = false;
	enemyPosition = { xPos, -100 };

	enemySprite.setPosition(enemyPosition);
	isAtGoalY = false;

}
