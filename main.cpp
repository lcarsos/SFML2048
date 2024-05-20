#include "Settings.h"
#include "color.h"

#include "game2048.h"

#include <SFML/Graphics.hpp>


int main() {

	Game2048 game;

	game.initSFML();
	game.mainLoop();

	return 0;
}