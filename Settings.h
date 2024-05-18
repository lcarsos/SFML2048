#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include <random> // For rng

#include <SFML/Graphics.hpp> // For colors

struct MySettings {

	static MySettings& getInstance() {
		static MySettings instance;
		return instance; // Returns a static reference to the MySettings struct
	}

	static constexpr int TARGET_FPS = 180;

	static constexpr int INITIAL_SCREEN_WIDTH = 1920; // Initial screen width, can be overriden if necessary (second MySDL_Renderer constructor)
	static constexpr int INITIAL_SCREEN_HEIGHT = 1080;

	static constexpr int windowMaxWidth = 1920;
	static constexpr int windowMaxHeight = 1080;

	static constexpr int gridRows = 4;
	static constexpr int gridCols = 4;

	static constexpr int gridCellSize = 192;
	static constexpr int gridCellSpacing = 16;

	// Calculate total width and height of the grid
	static constexpr int totalWidth = gridCols * gridCellSize + (gridCols + 1) * gridCellSpacing;
	static constexpr int totalHeight = gridRows * gridCellSize + (gridRows + 1) * gridCellSpacing;

	static constexpr int windowMinWidth = totalWidth;
	static constexpr int windowMinHeight = totalHeight;

	static struct colors2048 {
		sf::Color farBackColor = { 55, 55, 55, 255 };
		sf::Color backgroundColor = { 202, 190, 176, 255 };
		sf::Color gridColor = { 175, 161, 148, 255 };


		sf::Color cell2Color = { 233, 228, 218, 255 };
		sf::Color cell4Color = { 236,224,202,255 };
		sf::Color cell8Color = { 242,177,121,255 };
		sf::Color cell16Color = { 236,141,83,255 };
		sf::Color cell32Color = { 245,124,95,255 };
		sf::Color cell64Color = { 233,89,54,255 };
		sf::Color cell128Color = { 244,216,109 };
		sf::Color cell256Color = { 241,208,75,255 };
		sf::Color cell512Color = { 228,192,42,255 };
		sf::Color cell1024Color = { 237, 197,63,255 };
		sf::Color cell2048Color = { 236, 196, 5, 255 };
		sf::Color cell4096Color = { 60,116,50,255 };
		sf::Color cell8192Color = { 30, 29,25,255 };

		sf::Color numberColor = { 245,245,250,255 };

		sf::Color scoreBGColor = {};
	};

private:

	MySettings() {} // Don't delete constructor

};

struct RandomGenerator {
public:
	// Public method to get the singleton instance
	static RandomGenerator& get_instance() {
		static RandomGenerator instance; // Guaranteed to be destroyed, instantiated on first use.
		return instance;
	}

	// Public method to get a random number in the specified range
	int get_random_number(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(rng);
	}

	// Method to get a random row or column (0 to 3)
	int get_random_row_or_col() {
		std::uniform_int_distribution<int> dist(0, 3);
		return dist(rng);
	}

	// Method to get a random value either 2 or 4 based on a probability
	int get_random_2_or_4() {
		std::uniform_real_distribution<double> dist(0.0, 1.0);
		return dist(rng) < 0.9 ? 2 : 4; // 90% chance of 2, 10% chance of 4
	}

private:
	// Private constructor to prevent instantiation
	RandomGenerator() : rng(std::random_device{}()) {}

	// Random number generator
	std::mt19937 rng;

	// Delete copy constructor and copy assignment operator to prevent copying
	RandomGenerator(const RandomGenerator&) = delete;
	RandomGenerator& operator=(const RandomGenerator&) = delete;
};

#endif