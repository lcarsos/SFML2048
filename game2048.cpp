#include "game2048.h"
#include "grid.h"

Game2048::Game2048() : screenWidth(settings.INITIAL_SCREEN_WIDTH), screenHeight(settings.INITIAL_SCREEN_HEIGHT){}

void Game2048::initSFML() {
	window.create(sf::VideoMode(screenWidth, screenHeight), "Window", sf::Style::Default);
}


void Game2048::splash() {}

void Game2048::mainLoop() {
	while (window.isOpen()) {
		handleEvents();
		updateLogic();
		renderGame();
	}
}

void Game2048::victory() {}

void Game2048::replay() {}


void Game2048::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void Game2048::updateLogic() {}

void Game2048::renderGame() {}


sf::Window* Game2048::getWindowPointer() {
	return &window;
}



