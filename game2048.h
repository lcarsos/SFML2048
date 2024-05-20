#pragma once


#ifndef GAME2048_H
#define GAME2048_H

#include "Settings.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "grid.h"

class Game2048 {
public:

	Game2048();


	void initSFML();
	void quit();

	void splash();
	void mainLoop();
	void victory();
	void replay();

	void handleEvents();
	void updateLogic();
	void renderGame();


	sf::RenderWindow* getWindowPointer();


private:
	sf::RenderWindow window;
	MySettings& settings = MySettings::getInstance();

	int screenWidth;
	int screenHeight;

	Grid grid;

};


#endif
