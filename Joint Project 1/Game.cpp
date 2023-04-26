// Name: 
// Login: 
// Date: 
// Approximate time taken: 
//---------------------------------------------------------------------------
// Project description: TEMPLATE
// ---------------------------------------------------------------------------
// Known Bugs:
// ?

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib")




#include "Game.h"   // include Game header file


Bullet Game::playerBullet;
Player Game::myPlayer;
EnemyOne Game::floater;
std::array<EnemyTwo, MAX_ENEMIES> Game::enemies;
std::array<Bullet, MAX_ENEMIES +1> Game::enemyBullets;


int main()
{
	Game aGame;
	aGame.loadContent();
	aGame.run();

	return 0;
}

Game::Game() : window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Joint Project Game", sf::Style::Default)
// Default constructor
{
}

void Game::loadContent()
// Load the font file & setup the message string
{
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}

	// set up the message string 
	m_message.setFont(m_font);  // set the font for the text
	m_message.setCharacterSize(24); // set the text size
	m_message.setFillColor(sf::Color::White); // set the text colour
	m_message.setPosition(50, 10);  // its position on the screen

	//set up player character
	if (!myPlayer.texture.loadFromFile("ASSETS/IMAGES/character.png"))
	{
		std::cout << "error with font file file";
	}
	myPlayer.sprite.setTexture(myPlayer.texture);
	myPlayer.sprite.setTextureRect(sf::IntRect{ 0, 0, 48, 64 });
	myPlayer.sprite.setPosition(myPlayer.playerPosition);
	myPlayer.sprite.setOrigin(24, 32);
	//setup background elements:
	//fence

	if (!fenceTexture.loadFromFile("ASSETS/IMAGES/fence.png"))
	{
		std::cout << "error with background asset";
	}
	fenceTexture.setRepeated(true);
	fenceSprite.setTexture(fenceTexture);
	fenceSprite.setPosition(0, 600);
	fenceSprite.setTextureRect(sf::IntRect{0, 0, 1500, 57 });

	//ground

	if (!groundTexture.loadFromFile("ASSETS/IMAGES/ground.png"))
	{
		std::cout << "error with background asset";
	}

	groundTexture.setRepeated(true);
	groundSprite.setTexture(groundTexture);
	groundSprite.setPosition(0, 657);
	groundSprite.setTextureRect(sf::IntRect{0,0, 1500, 175 });

	//player bullet
	if (!playerBullet.texture.loadFromFile("ASSETS/IMAGES/fireball.png"))
	{
		std::cout << "error with bullet asset";
	}
	playerBullet.sprite.setTexture(playerBullet.texture);
	playerBullet.sprite.setTextureRect(sf::IntRect{ 0, 0, 64, 64 });
	playerBullet.sprite.setPosition(playerBullet.bulletPosition);
	playerBullet.sprite.setOrigin(32, 32);

	//enemy bullets
	for (int i = 0; i < enemyBullets.size(); i++) {
		Bullet& bullet = enemyBullets[i];
		

		bullet.sprite.setTexture(playerBullet.texture);
		bullet.sprite.setTextureRect(sf::IntRect{ 0, 0, 64, 64 });
		bullet.sprite.setPosition( - 100, -100);
		bullet.sprite.setOrigin(32, 32);
		bullet.speed = 8;
	}
	//floater 
	if (!floater.enemyTexture.loadFromFile("ASSETS/IMAGES/floater.png"))
	{
		std::cout << "error with enemyOne asset";
	}
	floater.enemySprite.setTexture(floater.enemyTexture);
	floater.enemySprite.setTextureRect(sf::IntRect{ 0, 0, 75, 75 });
	floater.enemySprite.setPosition(floater.enemyPosition);
	floater.enemySprite.setOrigin(37, 37);

	// enemy2

	
	for (int i = 0; i < enemies.size(); i++)
	{
		EnemyTwo& enemy = enemies[i]; //reference to the 

		enemy.setup();
	}

	//score message

	scoreMessage.setFont(m_font);  
	scoreMessage.setCharacterSize(24); 
	scoreMessage.setFillColor(sf::Color::White); 
	scoreMessage.setPosition(1400, 10);  

	//game over assets
	gameOverScreen.setFillColor(sf::Color::White);
	gameOverScreen.setSize(sf::Vector2f{700, 500});
	gameOverScreen.setPosition(400, 150);
	
	
	gameOverText.setFont(m_font);
	gameOverText.setCharacterSize(30);
	gameOverText.setFillColor(sf::Color::Black);
	gameOverText.setPosition(650,300 );


	continueButton.setFillColor(sf::Color::Green);
	continueButton.setSize(sf::Vector2f{150,50});
	continueButton.setPosition(530, 500);


	exitButton.setFillColor(sf::Color::Red);
	exitButton.setSize(sf::Vector2f{150, 50});
	exitButton.setPosition(820, 500);


	continueText.setFont(m_font);
	continueText.setCharacterSize(24);
	continueText.setFillColor(sf::Color::Black);
	continueText.setPosition(550, 500);
	continueText.setString("Try again?");


	exitText.setFont(m_font);
	exitText.setCharacterSize(24);
	exitText.setFillColor(sf::Color::Black);
	exitText.setPosition(870, 500);
	exitText.setString("Exit");


}


void Game::run()
// This function contains the main game loop which controls the game. 
{

	srand((int)time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			if (myPlayer.lives > 0)
			{
				update();
			}
			else {
				gameOver();
			}
			draw();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}

void Game::update()
// This function takes the keyboard input and updates the game world
{
	// update any game variables here ...


	revive();

	for (int i = 0; i < enemies.size(); i++)
	{
		EnemyTwo& enemy = enemies[i];
		if (enemy.isAlive)
		{
			if (enemy.canMove)
			{
				enemy.move();
			}
			else
			{
				enemy.spawn(i);
			}
		}
		
	}

	if (floater.isAlive)
	{
		if (!floater.isAtGoalY)
		{
			floater.startMove();
		}
		else
		{
			floater.move();
		}

	}

	if (playerBullet.canMove)
	{
		playerBullet.move(true);  //this is the player bullet, which moves upward.
		if (playerBullet.detectHit())
		{
			addScore();
		}
	}

	for (int i = 0; i <= MAX_ENEMIES; i++) //bullet movements and hit detection for all enemies
	{
		if (enemyBullets[i].canMove)
		{
			enemyBullets[i].move(false);
			if (enemyBullets[i].detectHitOnPlayer())
			{
				myPlayer.takeDamage();
			}
		}
	}
	//BUG: the enemyTwos are hoarding all the enemy bullets. 
	//enemy2 at index 0 will spawn all created bullets when he is righ above the player. 


	if (floater.enemyPosition.x - myPlayer.playerPosition.x > -SHOOT_RANGE && //if player is in shooting range and no bullet is already moving
		floater.enemyPosition.x - myPlayer.playerPosition.x < SHOOT_RANGE &&
		enemyBullets[8].canMove == false && 
		floater.isAlive)

	{

		enemyBullets[8].spawn(FLOATER_INDEX);  //the bullet at index 8 is reserved for the floater.
		enemyBullets[8].canMove = true;
		std::cout << "spawned bullet 8\n";
	}

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		EnemyTwo& enemy = enemies[i];
		if (abs(enemy.enemy2Position.x - myPlayer.playerPosition.x) < SHOOT_RANGE &&
			enemyBullets[i].canMove == false &&
			enemy.isAlive)

		{

			enemyBullets[i].spawn(i); //each enemy has a singular bullet they can fire
			std::cout << "spawned bullet " << i << "\n";
			enemyBullets[i].canMove = true;
		}
	}

	

	// get keyboard inputs
	//movement keypresses:
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		myPlayer.move();  //moves the player
	}

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !playerBullet.canMove) //spawns the player bullet
	{
		playerBullet.spawn(PLAYER_INDEX);
		playerBullet.canMove = true;
		
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && myPlayer.dashRestartClock) //spawns the player bullet
	{
		myPlayer.isDashing = true;

	}

	if (myPlayer.isDashing)
	{
		myPlayer.dash();
	}

}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	window.clear();

		window.draw(m_message);  // write message to the screen
		window.draw(scoreMessage);
		window.draw(groundSprite);
		window.draw(fenceSprite);
		window.draw(myPlayer.sprite);
		for (int i = 0; i < enemies.size(); i++) //draws all enemyTwos
		{
			EnemyTwo& enemy = enemies[i];
			window.draw(enemy.enemy2Sprite);
		}
		window.draw(floater.enemySprite);
		window.draw(playerBullet.sprite);
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			window.draw(enemyBullets[i].sprite);
		}
		m_message.setString("Lives: " + std::to_string(myPlayer.lives));
	if (myPlayer.lives < 1)
	{
		std::cout << "game over screen draing\n";
		window.draw(gameOverScreen);
		window.draw(continueButton);
		window.draw(exitButton);
		window.draw(gameOverText);
		window.draw(continueText);
		window.draw(exitText);
	}
	
	window.display();
}

void Game::revive()//sets enemies as alive after random intervals, handles how many enemies there are at once.
//DOESNT WORK, but should make sense.
{
	float timeElapsed = runtimeClock.getElapsedTime().asSeconds();

	if (floaterClockStart) //these clocks need to be set up once, then restarted only once needed. 
							//this if statement prevents it from being called continuously
	{
		floaterSpawnClock.restart();
		floaterClockStart = false;
	}

	floaterSpawnTime = floaterSpawnClock.getElapsedTime().asSeconds();

	if (enemyTwoClockStart)
	{
		enemyTwoSpawnClock.restart();
		enemyTwoClockStart = false;
	}

	enemyTwoSpawnTime = enemyTwoSpawnClock.getElapsedTime().asSeconds();

	srand(time(0));
	int floaterSpawn = rand() % 10 + 3;
	int enemyTwoSpawn = rand() % 5 + 3;

	if (floaterSpawn < floaterSpawnTime) //spawns a wae of all aailable enemies 
	{   
		floater.isAlive = true;
		floaterClockStart = true;
	}

	if (enemyTwoSpawn < enemyTwoSpawnTime)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			EnemyTwo& enemy = enemies[i];
			if (i < (timeElapsed / ENEMY_TWO_SPAWN_TIME))   //sets 1 extra enemy per the amount of seconds.
			{
				enemy.isAlive = true;
			}


		}
		enemyTwoClockStart = true;
	}
}

void Game::addScore()
{
	score += 50;
	scoreMessage.setString(std::to_string( score ));

}

void Game::gameOver() //game over screen
{
	
	sf::Vector2i mouseCoordinates = sf::Mouse::getPosition(window);
	sf::IntRect continueButtonRect ={ 530, 500, 150, 50 };
	sf::IntRect exitButtonRect = {820, 500, 150, 50};

	gameOverText.setString("      You ran out lives! \n            Score: " + std::to_string(score));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && continueButtonRect.contains(mouseCoordinates)) //resets everything important to starting value
	{
		myPlayer.lives = 3;
		score = 0;
		floaterSpawnClock.restart();
		enemyTwoSpawnClock.restart();
		runtimeClock.restart();
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			enemies[i].death();
		}
		floater.death();
		playerBullet.death();

		for (int i = 0; i < MAX_ENEMIES + 1; i++)
		{
			enemyBullets[i].death();
		}
		myPlayer.playerPosition = { 750, 700 };
		myPlayer.sprite.setPosition(myPlayer.playerPosition);

	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitButtonRect.contains(mouseCoordinates))
	{
		window.close();
	}

}
