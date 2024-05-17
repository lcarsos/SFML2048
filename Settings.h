#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

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
		/*SDL_Color farBackColor = { 76, 76, 76, 100 };
		SDL_Color backgroundColor = { 202, 190, 176, 255 };
		SDL_Color gridColor = { 175, 161, 148, 255 };


		SDL_Color cell2Color = { 233, 228, 218, 255 };
		SDL_Color cell4Color = { 236,224,202,255 };
		SDL_Color cell8Color = { 242,177,121,255 };
		SDL_Color cell16Color = { 236,141,83,255 };
		SDL_Color cell32Color = { 245,124,95,255 };
		SDL_Color cell64Color = { 233,89,54,255 };
		SDL_Color cell128Color = { 244,216,109 };
		SDL_Color cell256Color = { 241,208,75,255 };
		SDL_Color cell512Color = { 228,192,42,255 };
		SDL_Color cell1024Color = { 237, 197,63,255 };
		SDL_Color cell2048Color = { 236, 196, 5, 255 };
		SDL_Color cell4096Color = { 60,116,50,255 };
		SDL_Color cell8192Color = { 30, 29,25,255 };

		SDL_Color numberColor = { 245,245,250,255 };

		SDL_Color scoreBGColor = {};*/
	};

private:

	MySettings() {} // Don't delete constructor

};

#endif