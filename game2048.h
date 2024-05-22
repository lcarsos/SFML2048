#pragma once


#ifndef GAME2048_H
#define GAME2048_H

#include "Settings.h"
#include "color.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

#include "grid.h"

class Game2048 {
public:

	Game2048();


	void initSFML();
	void initFont();
	void quit();

	void splash();
	void mainLoop();
	void victory();
	void loss();

	void handleEvents();
	void updateLogic();
	void renderGame();


	sf::RenderWindow& getWindow();


private:
	sf::RenderWindow window;
	MySettings& settings = MySettings::getInstance();

	sf::View view = window.getDefaultView();

	int screenWidth;
	int screenHeight;

	const int& cellSpacing = settings.gridCellSpacing;
	const int& cellSize = settings.gridCellSize;
	const int& rows = settings.gridRows;
	const int& cols = settings.gridCols;

	int paddingWidth = (screenWidth / 2) - (settings.totalHeight / 2);
	int paddingHeight = (screenHeight / 2) - (settings.totalHeight / 2) + (settings.scoreBoxHeight / 2);

	Grid grid;

	sf::RectangleShape bgRect;

	sf::Font font;

	struct colors2048 {
		const sf::Color farBackColor = { 55, 55, 55, 255 };
		const sf::Color backgroundColor = { 200, 188, 174, 255 };
		const sf::Color gridColor = { 175, 161, 148, 255 };


		const sf::Color cell2Color = { 233, 228, 218, 255 };
		const sf::Color cell4Color = { 236,224,202,255 };
		const sf::Color cell8Color = { 242,177,121,255 };
		const sf::Color cell16Color = { 236,141,83,255 };
		const sf::Color cell32Color = { 245,124,95,255 };
		const sf::Color cell64Color = { 233,89,54,255 };
		const sf::Color cell128Color = { 244,216,109 };
		const sf::Color cell256Color = { 241,208,75,255 };
		const sf::Color cell512Color = { 228,192,42,255 };
		const sf::Color cell1024Color = { 237, 197,63,255 };
		const sf::Color cell2048Color = { 236, 196, 5, 255 };
		const sf::Color cell4096Color = { 60,116,50,255 };
		const sf::Color cell8192Color = { 30, 29,25,255 };

		const sf::Color numberColor = { 244,244,249,255 };

		const sf::Color scoreBGColor = { 200, 188, 174, 255 };

	} colors2048;

	const std::map<int, sf::Color> colorMap = {
	{2, colors2048.cell2Color},
	{4, colors2048.cell4Color},
	{8, colors2048.cell8Color},
	{16, colors2048.cell16Color},
	{32, colors2048.cell32Color},
	{64, colors2048.cell64Color},
	{128, colors2048.cell128Color},
	{256, colors2048.cell256Color},
	{512, colors2048.cell512Color},
	{1024, colors2048.cell1024Color},
	{2048, colors2048.cell2048Color},
	{4096, colors2048.cell4096Color},
	{8192, colors2048.cell8192Color},
	// Add more mappings as needed for higher numbers...
	};

	void initBG();
	void renderBG();


	sf::Color getColorForNumber(int number) const;
	void renderNumber(int num, int xPos, int yPos);
	void renderGrid();
	void renderCell();

	void renderScoreBox();

	void enforceWindowSizeConstraints(const int& minSizeX, const int& minSizeY, const int& maxSizeX, const int& maxSizeY);
};


#endif
