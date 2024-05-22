#include "game2048.h"
#include "grid.h"

Game2048::Game2048() : screenWidth(settings.INITIAL_SCREEN_WIDTH), screenHeight(settings.INITIAL_SCREEN_HEIGHT), grid() {}

void Game2048::initSFML() {
	window.create(sf::VideoMode(screenWidth, screenHeight), "Window", sf::Style::Default);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	initFont();
}

void Game2048::initFont() {

	if (!font.loadFromFile(".\\Montserrat-Regular.ttf")) {
		std::cout << "FUck!";
	}

}

void Game2048::quit() {
	// May be redundant
}


void Game2048::splash() {
	// Display "Another 2048 Clone!" on reg bg
	// Switch to main loop after 3ish seconds

	window.clear();

	const std::string victoryMessage = "Another 2048 clone!\n";
	const std::string playAgainMessage = "Malcolm LaRose 2024\n";

	const std::string textToDisplay = victoryMessage + playAgainMessage;
	const int fontSize = 66;

	// Split the text into lines
	std::vector<std::string> lines;
	std::istringstream stream(textToDisplay);
	std::string line;
	while (std::getline(stream, line, '\n')) {
		lines.push_back(line);
	}

	int i = 0;
	std::vector<sf::Text> texts;
	for (const auto& l : lines) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(fontSize - i*12);
		text.setFillColor(colors2048.cell2048Color);
		text.setString(l);
		texts.push_back(text);
		i++;
	}

	// Calculate the total height
	float totalHeight = 0;
	for (const auto& text : texts) {
		totalHeight += text.getLocalBounds().height + fontSize * 0.2f; // Adjust the spacing as needed
	}

	// Position the text lines
	sf::Vector2u windowSize = window.getSize();
	float startY = (windowSize.y - totalHeight) / 2.0f;

	for (size_t i = 0; i < texts.size(); ++i) {
		auto& text = texts[i];
		auto textWidth = text.getLocalBounds().width;
		text.setPosition((windowSize.x - textWidth) / 2.0f, startY);
		startY += text.getLocalBounds().height + fontSize * 0.2f; // Adjust the spacing as needed
	}

	renderBG();
	for (const auto& text : texts) {
		window.draw(text);
	}
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	sf::Event event;
	while (window.pollEvent(event)) {/* Clear event queue?*/}

}

void Game2048::mainLoop() {
	initBG();
	splash();

	while (window.isOpen()) {
		handleEvents();
		updateLogic();
		renderGame();
		// grid.logGridState();
	}
}

void Game2048::victory() { // Rendering loop, will be stuck here until action is taken
	window.clear();

	const std::string victoryMessage = "Congratulations, you won!\n";
	const std::string playAgainMessage = "Would you like to play again?\n";
	const std::string instructions = "y: play again \nn: quit \nc: continue playing";

	const std::string textToDisplay = victoryMessage + playAgainMessage + instructions;
	const int fontSize = 60;

	// Split the text into lines
	std::vector<std::string> lines;
	std::istringstream stream(textToDisplay);
	std::string line;
	while (std::getline(stream, line, '\n')) {
		lines.push_back(line);
	}

	std::vector<sf::Text> texts;
	for (const auto& l : lines) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(fontSize);
		text.setFillColor(colors2048.cell2048Color);
		text.setString(l);
		texts.push_back(text);
	}

	// Calculate the total height
	float totalHeight = 0;
	for (const auto& text : texts) {
		totalHeight += text.getLocalBounds().height + fontSize * 0.2f; // Adjust the spacing as needed
	}

	// Position the text lines
	sf::Vector2u windowSize = window.getSize();
	float startY = (windowSize.y - totalHeight) / 2.0f;

	for (size_t i = 0; i < texts.size(); ++i) {
		auto& text = texts[i];
		auto textWidth = text.getLocalBounds().width;
		text.setPosition((windowSize.x - textWidth) / 2.0f, startY);
		startY += text.getLocalBounds().height + fontSize * 0.2f; // Adjust the spacing as needed
	}

	renderBG();

	bool inputDetected = false;

	window.clear(colors2048.farBackColor);
	renderBG();
	for (const auto& text : texts) {
		window.draw(text);
	}

	while (!inputDetected) {
		// std::cout << "Stuck in victory loop" << std::endl;

		// Detect input here

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.scancode == sf::Keyboard::Scan::Y) {
					// Play again
					grid.clearGrid();
					return;
				}
				else if (event.key.scancode == sf::Keyboard::Scan::N) {
					// Change message and leave
					// Change message and leave
					sf::Text endText;
					endText.setFont(font);
					endText.setCharacterSize(fontSize);
					endText.setFillColor(colors2048.cell2048Color);
					endText.setString("Thanks for playing!");

					auto endTextWidth = endText.getLocalBounds().width;
					endText.setPosition((windowSize.x - endTextWidth) / 2.0f, windowSize.y / 2.0f - endText.getLocalBounds().height / 2.0f);

					window.clear(colors2048.farBackColor);
					window.draw(endText);
					window.display();
					std::this_thread::sleep_for(std::chrono::milliseconds(3000));

					window.close();
					return;
				}
				else if (event.key.scancode == sf::Keyboard::Scan::C) {
					// Play again
					ignoreWin = true;
					return;
				}
			}
			window.display();
		
		}

	}
	// Display winning screen with victory message and score (and maybe movecount?)
	// If playagain, call replay()
	// If continue, go back to main loop
	// If done, quit game

}

void Game2048::loss() {
	window.clear();

	const std::string victoryMessage = "You have been slain!\n";
	const std::string playAgainMessage = "Would you like to play again?\n";
	const std::string instructions = "y: play again \nn: quit";

	const std::string textToDisplay = victoryMessage + playAgainMessage + instructions;
	const int fontSize = 60;

	// Split the text into lines
	std::vector<std::string> lines;
	std::istringstream stream(textToDisplay);
	std::string line;
	while (std::getline(stream, line, '\n')) {
		lines.push_back(line);
	}

	std::vector<sf::Text> texts;
	for (const auto& l : lines) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(fontSize);
		text.setFillColor(colors2048.cell2048Color);
		text.setString(l);
		texts.push_back(text);
	}

	// Calculate the total height
	float totalHeight = 0;
	for (const auto& text : texts) {
		totalHeight += text.getLocalBounds().height + fontSize * 0.2f; // Adjust the spacing as needed
	}

	// Position the text lines
	sf::Vector2u windowSize = window.getSize();
	float startY = (windowSize.y - totalHeight) / 2.0f;

	for (size_t i = 0; i < texts.size(); ++i) {
		auto& text = texts[i];
		auto textWidth = text.getLocalBounds().width;
		text.setPosition((windowSize.x - textWidth) / 2.0f, startY);
		startY += text.getLocalBounds().height + fontSize * 0.2f; // Adjust the spacing as needed
	}

	renderBG();

	bool inputDetected = false;

	window.clear(colors2048.farBackColor);
	renderBG();
	for (const auto& text : texts) {
		window.draw(text);
	}

	while (!inputDetected) {
		// std::cout << "Stuck in victory loop" << std::endl;
		// Detect input here

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.scancode == sf::Keyboard::Scan::Y) {
					// Play again
					grid.clearGrid();
					return;
				}
				else if (event.key.scancode == sf::Keyboard::Scan::N) {
					// Change message and leave
					// Change message and leave
					sf::Text endText;
					endText.setFont(font);
					endText.setCharacterSize(fontSize);
					endText.setFillColor(colors2048.cell2048Color);
					endText.setString("Thanks for playing!");

					auto endTextWidth = endText.getLocalBounds().width;
					endText.setPosition((windowSize.x - endTextWidth) / 2.0f, windowSize.y / 2.0f - endText.getLocalBounds().height / 2.0f);

					window.clear(colors2048.farBackColor);
					window.draw(endText);
					window.display();
					std::this_thread::sleep_for(std::chrono::milliseconds(3000));

					window.close();
					return;
				}
			}
			window.display();

		}

	}

}


void Game2048::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up) {
				grid.moveAndMergeUp();
			}
			else if ((event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::Left)) {
				grid.moveAndMergeLeft();
			}
			else if ((event.key.scancode == sf::Keyboard::Scan::S || event.key.scancode == sf::Keyboard::Scan::Down)) {
				grid.moveAndMergeDown();
			}
			else if ((event.key.scancode == sf::Keyboard::Scan::D || event.key.scancode == sf::Keyboard::Scan::Right)) {
				grid.moveAndMergeRight();
			}
			else if (event.key.scancode == sf::Keyboard::Scan::R) { // DEBUG CONTROL
				grid.clearGrid();
			}
			else if (event.key.scancode == sf::Keyboard::Scan::K) { // DEBUG CONTROL
				grid.placeWinningTile();
			}
			else if (event.key.scancode == sf::Keyboard::Scan::Q) {
				window.close();
			}
			break;
		case sf::Event::Resized:
			enforceWindowSizeConstraints(settings.windowMinWidth, settings.windowMinHeight, settings.windowMaxWidth, settings.windowMaxHeight);

			screenWidth = event.size.width;
			screenHeight = event.size.height;

			//paddingWidth = (screenWidth / 2) - (settings.totalHeight / 2);
			//paddingHeight = (screenHeight / 2) - (settings.totalHeight / 2) + (settings.scoreBoxHeight / 2);

			//// Update the view to the new size, keeping aspect ratio
			//sf::FloatRect visibleArea((settings.INITIAL_SCREEN_WIDTH - screenWidth) / 2, (settings.INITIAL_SCREEN_HEIGHT - screenHeight)/2, screenWidth, screenHeight);
			//view = sf::View(visibleArea);
			//window.setView(view);

			

			break;
		//default:
			break;


		}
	}
}

void Game2048::updateLogic() {
	if (grid.checkForWin() && !ignoreWin) {
		std::cout << "V" << std::endl;
		victory();
	}
	if (grid.isFull()) {
		std::cout << "L" << std::endl;
		loss();
	}
}

void Game2048::renderGame() {
	window.clear(); // Can (maybe?) avoid if we draw bg rectangle that covers window
	renderBG();
	renderGrid();
	renderScoreBox();
	renderCell();

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

sf::Color Game2048::getColorForNumber(int number) const {
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

void Game2048::renderNumber(int num, int xPos, int yPos) {
	int fontSizeLarge = 100;
	int fontSizeMed = 78;
	int fontSizeSmall = 62;

	sf::Text text;
	text.setFont(font);

	if (num >= 1024) {
		text.setCharacterSize(fontSizeMed);
	}
	else if (num > 8192) {
		text.setCharacterSize(fontSizeSmall);
	}
	else {
		text.setCharacterSize(fontSizeLarge);
	}

	text.setFillColor(colors2048.numberColor);
	text.setString(std::to_string(num));

	// Calculate the position for the text to be centered
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(xPos + settings.gridCellSize / 2, yPos + settings.gridCellSize / 2));



	window.draw(text);
}


void Game2048::renderCell() {
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid.checkForCellAt(i, j)) {

				Cell& cell = grid.getCellAt(i, j);

				// Set color for cells
				sf::Color cellColor = getColorForNumber((grid.getCellAt(i, j)).getNumber());

				int topLeftX = cellSpacing * (j + 1) + cellSize * j;
				int topLeftY = cellSpacing * (i + 1) + cellSize * i;

				sf::RectangleShape cellRect;

				cellRect.setPosition(topLeftX += paddingWidth, topLeftY += paddingHeight);
				cellRect.setSize(sf::Vector2f(cellSize, cellSize));

				cellRect.setFillColor(cellColor);
				window.draw(cellRect);

				

				// Place text here
				renderNumber(cell.getNumber(), topLeftX, topLeftY);


			}
		}
	}

}

void Game2048::renderGrid() {
	sf::Color gridColor = colors2048.gridColor;

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


void Game2048::renderScoreBox() {

	// Render Box
	const int& width = settings.scoreBoxWidth - 2*cellSpacing;
	const int& height = settings.scoreBoxHeight;

	int topLeftX = paddingWidth + cellSpacing; // Can we make this a reference?
	int topLeftY = paddingHeight - height;

	sf::Vector2f topLeft(topLeftX, topLeftY);

	sf::RectangleShape scoreBox;
	scoreBox.setSize(sf::Vector2f(width, height));
	scoreBox.setPosition(topLeftX, topLeftY);
	scoreBox.setFillColor(colors2048.scoreBGColor);
	scoreBox.setOutlineThickness(settings.gridCellSpacing);
	scoreBox.setOutlineColor(colors2048.gridColor);

	// Render Score

	int fontSizeLarge = 90;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(fontSizeLarge);
	text.setFillColor(colors2048.numberColor);
	text.setString("Score: " + std::to_string(grid.getScore()));

	// Calculate the position for the text to be centered
	sf::FloatRect textRect = text.getLocalBounds();

	// Calculate the center position for the score box
	float boxCenterX = topLeftX + width / 2.0f;
	float boxCenterY = topLeftY + height / 2.0f;

	// Set the origin to the center of the text's bounding box
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	// Set the text position to the center of the score box
	text.setPosition(boxCenterX, boxCenterY);


	// Draw box and score
	window.draw(scoreBox);
	window.draw(text);



}

void Game2048::enforceWindowSizeConstraints(const int& minSizeX, const int& minSizeY, const int& maxSizeX, const int& maxSizeY) {
	sf::Vector2u size = window.getSize();
	if (size.x < minSizeX) size.x = minSizeX;
	if (size.x > maxSizeX) size.x = maxSizeX;
	if (size.y < minSizeY) size.y = minSizeY;
	if (size.y > maxSizeY) size.y = maxSizeY;
	if (size != window.getSize()) {
		window.setSize(size);
	}
}