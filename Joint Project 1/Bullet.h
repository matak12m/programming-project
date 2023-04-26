#pragma once
// Bullet class declaration
#pragma once
#include "SFML/Graphics.hpp"
#include "Globals.h"
class Bullet
{
	// private data members
	const int SPRITE_HEIGHT = 64;
	const int SPRITE_WIDTH = 48;
	int spriteRow = 0; //controls which textures are used for the sprite.
	
	
public:
	int speed = 15;
	bool canMove = false;
	void move(bool t_goingUp);  //moves the bullet
	bool detectHit(); //continously checks for collision with the edge of the screen or enemy/player.
	bool detectHitOnPlayer(); //called by enemy bullets.
	void spawn(int t_shooterIndex); //called by the enemy or the player     player: index = -2, floater: index = -1
	void death();

	sf::Sprite sprite;
	sf::Texture texture;

	sf::Vector2f bulletPosition = { 100, 100 };
};