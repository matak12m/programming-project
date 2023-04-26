#include "EnemyTwo.h"   // include enemy header file
#include "SFML/graphics.hpp"
#include "Game.h"
#include "random"




void EnemyTwo::setup()
{
	if (!enemy2Texture.loadFromFile("ASSETS/IMAGES/enemy2.png"))
	{
		std::cout << "error with enemyOne asset";
	}
	enemy2Sprite.setTexture(enemy2Texture);
	enemy2Sprite.setTextureRect(sf::IntRect{ 0, 0, 75, 75 });
	enemy2Sprite.setPosition(-100, -100);
	enemy2Sprite.setOrigin(37, 37);

}

void EnemyTwo::move()  //moves enemy from one side of the screen until it goes offscreen.
{


	if (moveRight && enemy2Position.x < 1900) {
		enemy2Position.x += speed;
		enemy2Sprite.setPosition(enemy2Position);
	}
	else if (!moveRight && enemy2Position.x>-400)
	{
		enemy2Position.x -= speed;
		enemy2Sprite.setPosition(enemy2Position);
	}
	else {
		death();
	}

}

void EnemyTwo::death() //kills the creature, sets it up for another iteration.
{
	isAlive = false;
	enemy2Position = { -100, -100 };
	enemy2Sprite.setPosition(enemy2Position);
	generateRandom = true;
	canMove = false;

}

void EnemyTwo::spawn(int t_randomizer) //decides which way the enemy will move, sets up the enemy start position.
{

	srand(time(0) * t_randomizer);
	speed = rand() % 5 + 2;
	int right = rand() % 2;

	if (right == 1)
	{
		moveRight = true;

		srand(time(0) * t_randomizer);
		int random = rand() % 399;
		enemy2Position.x = -random; //effectivelly randomizes the waves a little bit, so that the enemies aren't at the same spot
	}
	else
	{
		moveRight = false;

		srand(time(0)* t_randomizer);
		int random = rand() % 399 + 1500;
		enemy2Position.x = random; //effectivelly randomizes the waves a little bit, so that the enemies aren't at the same spot

	}
	int height = rand() % 200 + 50;
	enemy2Position.y = height;
	enemy2Sprite.setPosition(enemy2Position);
	generateRandom = false; //turns off this function.
	canMove = true;
}

