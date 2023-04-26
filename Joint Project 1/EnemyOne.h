#pragma once
#include "SFML/Graphics.hpp"
class EnemyOne {
private:
	int speed = 5;
	bool generateRandom = true;
	int moveToY = 300;
	float xPos;


public:
	bool moveRight = true;
	bool isAtGoalY = false;
	bool isAlive = false;
	bool canShoot = true;

	sf::Vector2f enemyPosition = { -100, -100 };
	sf::Sprite enemySprite;
	sf::Texture enemyTexture;
	void startMove(); //moves the enemy to the target Y level
	void move(); //moves the enemy for left and right
	void death(); //gets rid of enemy
	

};