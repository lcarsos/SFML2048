#include "game2048.h"
#include "grid.h"

Game2048::Game2048() : screenWidth(settings.INITIAL_SCREEN_WIDTH), screenHeight(settings.INITIAL_SCREEN_HEIGHT){}

void Game2048::initSFML() {
	window.create(sf::VideoMode(screenWidth, screenHeight), "Window", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
}

void Game2048::quit() {
	// May be redundant
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
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) {
			
			}
			else if ((event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::Left)) {
			
			}
			else if ((event.key.scancode == sf::Keyboard::Scan::S || event.key.scancode == sf::Keyboard::Scan::Down)) {

			}
			else if ((event.key.scancode == sf::Keyboard::Scan::D || event.key.scancode == sf::Keyboard::Scan::Right)) {

			}
			break;
		case sf::Event::Resized:
			screenWidth = event.size.width;
			screenHeight = event.size.height;
			break;
		default:
			break;


		}
	}
}

void Game2048::updateLogic() {}

void Game2048::renderGame() {}


sf::RenderWindow* Game2048::getWindowPointer() {
	return &window;
}



