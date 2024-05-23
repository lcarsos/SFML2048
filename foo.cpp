#include <stdio.h>

#include "grid.h"

typedef std::vector<std::vector<std::optional<Cell>>> GridData;

int main() {

    Grid grid = Grid();
    GridData initial = grid.getGridData();
    printf("%u\n", &initial);
    GridData before = grid.getGridData();
    printf("%u\n", &before);
    bool diff = grid.isSameGridState(initial, before);
    printf("diff is literally the same: %i\n", diff);
    grid.moveAndMergeLeft();
    grid.moveAndMergeUp();
    grid.moveAndMergeRight();
    grid.moveAndMergeDown();
    grid.moveAndMergeLeft();
    GridData after = grid.getGridData();
    printf("%u\n", &after);
    diff = grid.isSameGridState(before, after);
    printf("diff should actually be 0 now: %i\n", diff);
    printf("double check true: %i\n", true);
    printf("double check false: %i\n", false);


    return 0;
}
// output:
// 232038800
// 232038832
// diff is literally the same: 1
// Score: 8232038864
// diff should actually be 0 now: 0
// double check true: 1
// double check false: 0
