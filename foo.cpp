#include <stdio.h>

#include "grid.h"

typedef std::vector<std::vector<std::optional<Cell>>>& GridDataRef;

int main() {

    Grid grid = Grid();
    GridDataRef initial = grid.getGridData();
    printf("%u\n", &initial);
    GridDataRef before = grid.getGridData();
    printf("%u\n", &before);
    bool diff = grid.isSameGridState(initial, before);
    printf("diff is literally the same: %i\n", diff);
    grid.moveAndMergeLeft();
    grid.moveAndMergeUp();
    grid.moveAndMergeRight();
    grid.moveAndMergeDown();
    grid.moveAndMergeLeft();
    GridDataRef after = grid.getGridData();
    printf("%u\n", &after);
    diff = grid.isSameGridState(before, after);
    printf("diff should actually be 0 now: %i\n", diff);
    printf("double check true: %i\n", true);
    printf("double check false: %i\n", false);


    return 0;
}
// output:
// 3429998288
// 3429998288
// diff is literally the same: 1
// Score: 83429998288
// diff should actually be 0 now: 1
// double check true: 1
// double check false: 0
