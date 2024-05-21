#pragma once

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <optional>

#include "cell.h"
#include "score.h"

class Grid {
public:
	Grid();

	void logGridState(); // Debugging function

	bool isSameGridState(std::vector<std::vector<std::optional<Cell>>>& before, std::vector<std::vector<std::optional<Cell>>>& after);
	bool checkForCellAt(int row, int col);
	bool isFull();

	void placeRandomCell();

	void deleteCellAt(int row, int col);
	void clearGrid();

	void moveAndMergeLeft();
	void moveAndMergeRight();
	void moveAndMergeUp();
	void moveAndMergeDown();

	std::vector<std::vector<std::optional<Cell>>>& getGridData();
	Cell& getCellAt(int row, int col);
	int getScore();


private:
	static constexpr int rows = 4;
	static constexpr int cols = 4;
	static constexpr int cellSpacing = 20;
	static constexpr int cellSize = 200;

	std::vector<std::vector<std::optional<Cell>>> gridData;
	Score score;

	MySettings& settings = MySettings::getInstance();
	RandomGenerator& rng = RandomGenerator::get_instance();

	std::optional<Cell> getPotentialCellAt(int row, int col);
	bool adjacentLikeCells(Cell& chkCell);
	void moveCellTo(Cell& cell, int newRow, int newCol);
	void resetCellMergeFlag();
	void mergeCells(Cell& targetCell, Cell& movingCell);
	int randomTwoOrFour();
	Cell createCell(int row, int col);

};

#endif
