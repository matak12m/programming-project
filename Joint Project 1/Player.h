// Player class declaration
#pragma once
#include "SFML/Graphics.hpp"
class Player
{
	// private data members
	int speed = 20;
	const int SCREEN_WIDTH = 1500;   // the size of the screen in pixels used in the game
	const int SCREEN_HEIGHT = 800;
	const int SPRITE_HEIGHT = 64;
	const int SPRITE_WIDTH = 48;
public:
	void move();
	sf::Sprite sprite;
    sf::Texture texture;

};