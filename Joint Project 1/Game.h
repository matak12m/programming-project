// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Globals.h"   // include Global header file
#include "Player.h"   // include Player header file
#include "Bullet.h"
#include "EnemyOne.h"
#include "EnemyTwo.h"
#include <array>

class Game
{
	
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	sf::RectangleShape gameOverScreen;
	sf::RectangleShape continueButton;
	sf::RectangleShape exitButton;
	sf::Text gameOverText;
	sf::Text continueText;
	sf::Text exitText;

	sf::RenderWindow window;
	sf::Clock floaterSpawnClock;
	sf::Clock enemyTwoSpawnClock;
	sf::Clock runtimeClock;
	sf::Text scoreMessage;
	int score = 0;

	bool floaterClockStart = true;
	bool enemyTwoClockStart = true;

	float floaterSpawnTime = 1;
	float enemyTwoSpawnTime = 1; //these need to be declared here because declaring a variable inside an if statement
								 //makes it's scope that if statement - but the variable cannot be declared every time
								 //the function is called


public:
	static Player myPlayer;
	static Bullet playerBullet;
	static EnemyOne floater;
	static std::array<EnemyTwo, MAX_ENEMIES> enemies;
	static std::array<Bullet, MAX_ENEMIES + 1> enemyBullets;

	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	sf::Texture
		fenceTexture,
		groundTexture;
	sf::Sprite
		fenceSprite,
		groundSprite;
	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent();
	void	run();
	void	update();
	void	draw();
	void revive(); //sets enemies as alive depending on the time in the game.
	void addScore();
	void gameOver();
};
