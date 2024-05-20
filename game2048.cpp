#include "game2048.h"
#include "grid.h"

Game2048::Game2048() : screenWidth(settings.INITIAL_SCREEN_WIDTH), screenHeight(settings.INITIAL_SCREEN_HEIGHT) {}

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
	initBG();
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
			// bgRect.setSize(sf::Vector2f(screenWidth, screenHeight));
			break;
		default:
			break;


		}
	}
}

void Game2048::updateLogic() {}

void Game2048::renderGame() {
	window.clear(); // Can (maybe?) avoid if we draw bg rectangle that covers window
	renderBG();
	renderGrid();

	window.display();

}


sf::RenderWindow& Game2048::getWindow() {
	return window;
}

void Game2048::initBG() {
	bgRect.setSize(sf::Vector2f(screenWidth, screenHeight));
	bgRect.setFillColor(Color::getSFMLColorVector(Color::EIGENGRAU));
	bgRect.setPosition(0, 0);
}

void Game2048::renderBG() {
	window.draw(bgRect);
}

sf::Color Game2048::getColorForNumber(int number) {
	// Check if the number exists in the map
	auto it = colorMap.find(number);
	if (it != colorMap.end()) {
		// Return the corresponding color
		return it->second;
	}
	else {
		// Default color if number doesn't exist in map
		exit(1);
	}
}

void Game2048::renderGrid() {
	sf::Color gridColor = colors2048.gridColor;

	int paddingWidth = (screenWidth / 2) - (settings.totalHeight / 2);
	int paddingHeight = (screenHeight / 2) - (settings.totalHeight / 2);

	// Render grid background
	sf::RectangleShape gridBGRect;
	gridBGRect.setPosition(paddingWidth, paddingHeight);
	gridBGRect.setSize(sf::Vector2f(settings.totalWidth, settings.totalHeight));
	gridBGRect.setFillColor(colors2048.backgroundColor);
	window.draw(gridBGRect);

	// Render vertical grid lines
	for (int col = 0; col < cols + 1; col++) {
		int x = (col)*cellSize + col * cellSpacing;
		sf::RectangleShape gridLineRect;

		int newY = 0;

		gridLineRect.setPosition(x += paddingWidth, newY += paddingHeight);
		gridLineRect.setSize(sf::Vector2f(cellSpacing, settings.totalHeight));

		gridLineRect.setFillColor(colors2048.gridColor);
		window.draw(gridLineRect);
	}

	// Render horizontal grid lines
	for (int row = 0; row < rows + 1; row++) {
		int y = (row)*cellSize + row * cellSpacing;
		sf::RectangleShape gridLineRect;

		int newX = 0;

		gridLineRect.setPosition(newX += paddingWidth, y += paddingHeight);
		gridLineRect.setSize(sf::Vector2f(settings.totalWidth, cellSpacing));

		gridLineRect.setFillColor(colors2048.gridColor);
		window.draw(gridLineRect);
	}
}


