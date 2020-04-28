# cryptarithmetic puzzles

## Problem Formulation

## Implementation Domain

To solve cryptarithmetic puzzles, currently we have implemented ...

Please keep in mind that, for the current implementation all the names specified above is actually expected as the parameter name.

## How to Run

General run command:
```
./puzzle -problem {PUZZLE_NAME} \
-algo {ALGORITHM_NAME} -mode {MODE} \
-board_dim {DIMENSION_OF_THE_BOARD} -mx_sideways_move {MAX_SIDEWAYS_MOVE}\
-print_path {PRINT_INITIAL_TO_GOAL}
```

Here is the parameter definition,
1. **-problem:** Specify the puzzle name to solve, for example, "n-queen".
2. **-algo:** Specify the search strategy to solve the puzzle, for example, "A*", "bfs", "dfs", etc.
3. **-mode:** Specify the inner methodology for the search strategy, for example, "bi-directional" bfs, "stack-based" dfs, etc.
4. **-board_dim:** Board dimension, may use representing any square board
5. **-mx_sideways_move:** Maximum allowed sideways move in hill-climbing search
6. **-print_path:** Flag to indicate printing path if solution exist, accepts boolean string, i.e., "true" or "false".

## Basic Algorithm Description & Run Commands


## Performance Characterization


### How to reproduce


### Performance of ...

**Observations:**

### Performance of ...

**Observations:**

## Future Works
* 

## Resources
* [Online Puzzle Solver] Cryptarithmetic Puzzle Solver: bach.istc.kobe-u.ac.jp/llp/crypt.html
