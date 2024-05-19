#include "grid.h"

Grid::Grid() {}

void Grid::logGridState() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (gridData[i][j].has_value()) {
				// Print the value of the optional cell if it exists
				printf("[%d]", gridData[i][j].value().getNumber());
			}
			else {
				// If cell is empty, print empty brackets
				printf("[]");
			}
			// Add space after each element except the last one in the row
			if (j < cols - 1) {
				printf(" ");
			}
		}
		printf("\n"); // Move to the next row
	}
}

bool Grid::isSameGridState(std::vector<std::vector<std::optional<Cell>>>& before, std::vector<std::vector<std::optional<Cell>>>& after) {
	// Iterate over each cell in the grid
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			// Check if both cells are empty
			if (!before[i][j].has_value() && !after[i][j].has_value()) {
				continue; // Move to the next cell
			}
			// Check if one cell is empty while the other is not
			if (!before[i][j].has_value() || !after[i][j].has_value()) {
				return false;
			}
			// Compare the numbers in non-empty cells
			if (before[i][j].value().getNumber() != after[i][j].value().getNumber()) {
				return false; // Numbers are different
			}
		}
	}

	// All cells are the same
	return true;
}

bool Grid::checkForCellAt(int row, int col) {
	// printf("row: %i col: %i", row, col);
	return (gridData[row][col]).has_value();
}

bool Grid::isFull() {
	const int capacity = rows * cols; // Total number of cells on the board
	int filledCells = 0; // Counter for filled cells

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (checkForCellAt(i, j)) {
				filledCells++; // Increment the filled cell count
			}
		}
	}

	if (filledCells == capacity) {
		// AND there are no viable moves left --> No two adjacent cells are identical
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				Cell& chkCell = getCellAt(i, j);
				if (!adjacentLikeCells(chkCell)) {
					return true;
				}
			}
		}
	}

	else {
		return false;
	}
}

void Grid::placeRandomCell() {
	int randRow, randCol;
	do {
		randRow = rng.get_random_row_or_col();
		randCol = rng.get_random_row_or_col();
	} while (checkForCellAt(randRow, randCol));

	Cell cell = createCell(randRow, randCol);
	gridData[randRow][randCol].emplace(cell);
}