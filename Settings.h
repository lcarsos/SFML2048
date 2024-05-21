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

	static constexpr int TARGET_FPS = 120;

	static constexpr int INITIAL_SCREEN_WIDTH = 1920; // Initial screen width, can be overriden if necessary (second MySDL_Renderer constructor)
	static constexpr int INITIAL_SCREEN_HEIGHT = 1080;

	static constexpr int windowMaxWidth = 1920;
	static constexpr int windowMaxHeight = 1080;

	static constexpr int gridRows = 4;
	static constexpr int gridCols = 4;

	static constexpr int gridCellSize = 192;
	static constexpr int gridCellSpacing = 16;

	static constexpr int scoreBoxHeight = 145;

	// Calculate total width and height of the grid
	static constexpr int totalWidth = gridCols * gridCellSize + (gridCols + 1) * gridCellSpacing;
	static constexpr int totalHeight = gridRows * gridCellSize + (gridRows + 1) * gridCellSpacing; // + (scoreBoxHeight + gridCellSpacing)

	static constexpr int windowMinWidth = totalWidth;
	static constexpr int windowMinHeight = totalHeight;

	static constexpr int scoreBoxWidth = totalWidth;

	static constexpr int deltaTime = 0.001; // seconds (1ms)



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