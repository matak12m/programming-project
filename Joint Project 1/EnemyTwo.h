
#pragma once
#include "SFML/Graphics.hpp"
class EnemyTwo {
private:
	int speed = 8;
	bool generateRandom = true;
	


public:
	bool moveRight = true;
	bool isAlive = false;
	bool canMove = false;

	sf::Vector2f enemy2Position = { 0, 0 };
	sf::Sprite enemy2Sprite;
	sf::Texture enemy2Texture;
	void setup();
	void move(); //moves the enemy for left and right
	void death(); //gets rid of enemy
	void spawn(int t_randomizer); //sets up enemy   //t_randomizer sets the enemies apart once they span.


};