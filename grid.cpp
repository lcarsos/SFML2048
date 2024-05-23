#include "grid.h"
#include "cell.h"
#include "score.h"

Grid::Grid() {
	gridData.resize(rows, std::vector<std::optional<Cell>>(cols));
	placeRandomCell();
}

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
		// printf("Row: %i, Col: %i", randRow, randCol);
	} while (checkForCellAt(randRow, randCol));

	Cell cell = createCell(randRow, randCol);
	gridData[randRow][randCol].emplace(cell);
}

void Grid::deleteCellAt(int row, int col) {
	gridData[row][col].reset();
}

void Grid::clearGrid() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			deleteCellAt(i, j);
		}
	}
	placeRandomCell();
	score.resetScore();
}

void Grid::placeWinningTile() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			deleteCellAt(i, j);
		}
	}
	Cell cell(2048, 1, 1);
	gridData[1][1].emplace(cell);
	
}

void Grid::moveAndMergeLeft() {

	std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

	for (int i = 0; i < settings.gridRows; i++) {
		for (int j = 1; j < settings.gridCols; j++) { // Start from the second column
			if (checkForCellAt(i, j)) {
				Cell& movingCell = getCellAt(i, j);
				int k = j - 1; // Index of the cell to the left

				// Move the cell as far left as possible
				while (k >= 0 && !checkForCellAt(i, k)) {
					moveCellTo(movingCell, i, k); // Move the cell to the left
					k--; // Move to the next left position
				}

				if (k >= 0 && checkForCellAt(i, k)) {
					Cell& targetCell = getCellAt(i, k);
					mergeCells(targetCell, movingCell);
				}
			}
		}
	}

	resetCellMergeFlag();

	std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

	if (!isSameGridState(beforeGrid, afterGrid)) {
		placeRandomCell();
	}

}

void Grid::moveAndMergeRight() {

	std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

	for (int i = 0; i < rows; i++) {
		for (int j = cols - 1; j >= 0; j--) { // Start from the second-to-last column and move leftwards
			if (checkForCellAt(i, j)) { // If there is a cell to move
				Cell& movingCell = getCellAt(i, j);
				int k = j + 1; // Index of the cell to the right

				// Move the cell as far right as possible
				while (k < cols && !checkForCellAt(i, k)) {
					moveCellTo(movingCell, i, k); // Move the cell to the right
					k++; // Move to the next right position
				}

				if (k < cols && checkForCellAt(i, k)) {
					Cell& targetCell = getCellAt(i, k);
					mergeCells(targetCell, movingCell);
				}
			}
		}
	}

	resetCellMergeFlag();

	std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

	if (!isSameGridState(beforeGrid, afterGrid)) {
		placeRandomCell();
	}

}


void Grid::moveAndMergeUp() {

	std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (checkForCellAt(i, j)) {
				Cell& movingCell = getCellAt(i, j);
				int k = i - 1; // Index of cell up

				// Move the cell as far up as possible
				while (k >= 0 && !checkForCellAt(k, j)) {
					moveCellTo(movingCell, k, j);
					k--;
				}

				if (k >= 0 && checkForCellAt(k, j)) { // Merge if possible
					Cell& targetCell = getCellAt(k, j);
					mergeCells(targetCell, movingCell);
				}
			}
		}
	}

	resetCellMergeFlag();

	std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

	if (!isSameGridState(beforeGrid, afterGrid)) {

		placeRandomCell();
	}

}

void Grid::moveAndMergeDown() {

	std::vector<std::vector<std::optional<Cell>>> beforeGrid = getGridData();

	for (int i = rows - 1; i >= 0; i--) {
		for (int j = 0; j < cols; j++) {
			if (checkForCellAt(i, j)) {
				Cell& movingCell = getCellAt(i, j);
				int k = i + 1; // Index of cell down

				// Move the cell as far down as possible
				while (k < rows && !checkForCellAt(k, j)) {
					moveCellTo(movingCell, k, j);
					k++;
				}

				if (k < rows && checkForCellAt(k, j)) { // Merge if possible
					Cell& targetCell = getCellAt(k, j);
					mergeCells(targetCell, movingCell);
				}
			}
		}
	}

	resetCellMergeFlag();

	std::vector<std::vector<std::optional<Cell>>> afterGrid = getGridData();

	if (!isSameGridState(beforeGrid, afterGrid)) {

		placeRandomCell();
	}

}

std::vector<std::vector<std::optional<Cell>>> Grid::getGridData() {

	return gridData;

}

Cell& Grid::getCellAt(int row, int col) {

	return gridData[row][col].value();

}

int Grid::getScore() {
	int& scr = score.getScore();
	return score.getScore();
}

std::optional<Cell> Grid::getPotentialCellAt(int row, int col) {
	return gridData[row][col];
}

bool Grid::adjacentLikeCells(Cell& chkCell) {

	int row = chkCell.getRow();
	int col = chkCell.getCol();

	// Check up (r - 1)
	if (row > 0) { // If we aren't on the top (bottom) row
		if (checkForCellAt(row - 1, col)) { // If there is a cell
			if (chkCell.getNumber() == getCellAt(row - 1, col).getNumber()) { // If those cells are equal
				return true;
			}
		}
	}

	// Check left
	else if (col > 0) { // If we aren't on the left col
		if (checkForCellAt(row, col - 1)) { // If there is a cell
			if (chkCell.getNumber() == getCellAt(row, col - 1).getNumber()) {
				return true;
			}
		}
	}

	// Check down
	else if (row < rows) { // If we aren't on the bottom (top) row
		if (checkForCellAt(row + 1, col)) { // If there is a cell
			if (chkCell.getNumber() == getCellAt(row + 1, col).getNumber()) {
				return true;
			}
		}
	}

	// Check right
	else if (col < cols) { // If we aren't on the left col
		if (checkForCellAt(row, col + 1)) { // If there is a cell
			if (chkCell.getNumber() == getCellAt(row, col + 1).getNumber()) {
				return true;
			}
		}
	}
	else return false;
}

void Grid::moveCellTo(Cell& cell, int newRow, int newCol) {
	int oldRow = cell.getRow();
	int oldCol = cell.getCol();

	if (oldRow != newRow || oldCol != newCol) { // check for valid moves
		// Change the value of row and col stored in the cell --> this should eventually be the only part of this function we need, somehow take care of the rest internally
		cell.setRow(newRow);
		cell.setCol(newCol); // --> ABSOLUTELY CRITICAL TO DO THIS BEFORE NEXT TWO STATEMENTS

		// Change the location in gridData
		gridData[newRow][newCol].emplace(cell);
		deleteCellAt(oldRow, oldCol);
	}
}

void Grid::resetCellMergeFlag() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (gridData[i][j].has_value()) {
				gridData[i][j].value().resetMerge();
			}
		}
	}
}

void Grid::mergeCells(Cell& targetCell, Cell& movingCell) {
	if ((targetCell.getNumber() == movingCell.getNumber()) && (!targetCell.hasCellMerged())) {
		// Merge the cells by updating the value of the first cell
		targetCell.setNumber((movingCell.getNumber()) * 2);
		// Update score
		score.updateScore(targetCell.getNumber());
		// Delete the second cell
		deleteCellAt(movingCell.getRow(), movingCell.getCol());
		// Log score to console for now
		score.logScore();
		targetCell.cellHasMerged();
		return;
	}

	else return;

}

bool Grid::checkForWin() {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (checkForCellAt(i, j)) {
				if (getCellAt(i, j).getNumber() == 2048) {
					return true;
				}
			}
		}
	}

	return false;

}

int Grid::randomTwoOrFour() {
	return rng.get_random_2_or_4();
}

Cell Grid::createCell(int row, int col) {
	return Cell(randomTwoOrFour(), row, col);
}
