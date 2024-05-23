#include "cell.h"
#include "Settings.h"

// Constructors
Cell::Cell(int row, int col)
    : number(2), row(row), col(col), justMerged(false) {}

Cell::Cell(int num, int row, int col)
    : number(num), row(row), col(col), justMerged(false) {}

Cell::~Cell() {
   // printf("Cell destroyed!");
}

// Copy constructor
Cell::Cell(const Cell& other)
    : number(other.number), row(other.row), col(other.col), justMerged(other.justMerged) {}

// Copy assignment operator
Cell& Cell::operator=(const Cell& other) {
    if (this != &other) {
        number = other.number;
        row = other.row;
        col = other.col;
        justMerged = other.justMerged;
    }
    return *this;
}

// Move constructor
Cell::Cell(Cell&& other) noexcept
    : number(std::move(other.number)), row(std::move(other.row)), col(std::move(other.col)), justMerged(std::move(other.justMerged)) {}

// Move assignment operator
Cell& Cell::operator=(Cell&& other) noexcept {
    if (this != &other) {
        number = std::move(other.number);
        row = std::move(other.row);
        col = std::move(other.col);
        justMerged = std::move(other.justMerged);
    }
    return *this;
}

// Getter methods
int Cell::getNumber() const noexcept {
    return number;
}

int Cell::getRow() const noexcept {
    return row;
}

int Cell::getCol() const noexcept {
    return col;
}

// Setter methods
void Cell::setNumber(int newNum) noexcept {
    number = newNum;
}

void Cell::setRow(int newRow) noexcept {
    row = newRow;
}

void Cell::setCol(int newCol) noexcept {
    col = newCol;
}

// Merge status methods
bool Cell::hasCellMerged() const noexcept {
    return justMerged;
}

void Cell::cellHasMerged() noexcept {
    justMerged = true;
}

void Cell::resetMerge() noexcept {
    justMerged = false;
}
