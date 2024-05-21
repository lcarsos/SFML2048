#pragma once

#ifndef CELL_H
#define CELL_H

#include "Settings.h"

class Cell {
public:
	// Constructors
	Cell(int row, int col);
	Cell(int num, int row, int col);

	// Destructor
	~Cell();

	// Copy constructor
	Cell(const Cell& other);

	// Copy assignment constructor
	Cell& operator=(const Cell& other);

	// Move constructor
	Cell(Cell&& other) noexcept;

	// Move assignment constructor
	Cell& operator=(Cell&& other) noexcept;


	int getNumber() const noexcept;
	int getRow() const noexcept;
	int getCol() const noexcept;

	void setNumber(int newNum) noexcept;
	void setRow(int newRow) noexcept;
	void setCol(int newCol) noexcept;


	bool hasCellMerged() const noexcept; // Ask if the cell just merged
	void cellHasMerged() noexcept; // Tell the cell it just merged
	void resetMerge() noexcept;


private:
	int number;
	int row, col;

	bool justMerged;

	MySettings& settings = MySettings::getInstance();


};

#endif 
