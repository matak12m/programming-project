// Player class declaration
#pragma once
#include "SFML/Graphics.hpp"
#include "Globals.h"
class Player
{
	// private data members
	int speed = 5;
	const int SPRITE_HEIGHT = 64;
	const int SPRITE_WIDTH = 48;
public:
	void move();
	sf::Sprite sprite;
    sf::Texture texture;
	sf::Vector2f playerPosition = {750, 700};
	sf::Clock dashClock;
	float dashTime = 0.5;      //the lenght of dash.
	float timeElapsed; //tracks dast time
	bool dashRestartClock = true; //tracks if a dash clock should be generated
	bool isDashing = false; //turns on the dashing state in update
	int lives = 3;
	void takeDamage();
	void dash();
};