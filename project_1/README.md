# Game Solver (by using problem solving techniques)

### Project goal

The goal of this project is to build a generic interactive plugable application for solving puzzles (i.e. 8-puzzle, 8-queen, Sudoku, etc.) using different problem solving techniques (i.e. informed search, uninformed search, etc.).
Here the plugable means, user can independently decide the search strategy along with the custom heuristic functions. If needed, user can choose to implement their own versions for them.

Besides, this application is designed in a way that, it will be a easy going platform for further extension of puzzles/strategy/heuristics.

### Restriction to use

For solving 8-puzzle game, I have implemented the algorithms (with the modes) listed bellow.

|  | bi-directional | greedy | recursive | stack-based |
| --- | --- | --- | --- | --- |
| a_star | - | - | - | - |
| ida_star | - | - | - | - |
| bfs | y | y | - | - |
| dfs | - | - | y | y |
| dls | y | - | - | - |
| ids | y | - | - | - |

### How to run
General run command:

```
./puzzle -problem {PUZZLE_NAME} -algo {ALGORITHM_NAME} -mode {MODE} -initial {INITIAL_STATE_OF_THE_GAME} -goal {GOAL_STATE_OF_THE_GAME}
```
For 8-puzzle game, here is the list of run commands for different implemented algorithms along with the corresponding mode.

* stack-based dfs
```
./puzzle -problem 8-puzzle -algo dfs -mode stack-based -initial 1,2,0,4,5,3,7,8,6 -goal 1,2,3,4,5,6,7,8,0
```

### Search strategies
A search strategy is defined by picking the order of node expansion, Strategies are evaluated along the following dimensions:
* Completeness: does it always find a solution if one exists?
* Optimality: does it always find a least-cost solution?
* Time complexity: number of nodes generated
* Space complexity: maximum number of nodes in memory

Time and space complexity are measured in terms of
* b: maximum branching factor of the search tree
* d: depth of the optimal solution
* m: maximum length of any path in the state space (may be infinite)

### Uninformed search strategies
Uninformed search strategies use only the information available in the problem definition
* Breadth-first search
* Uniform-cost search
* Depth-first search
* Iterative deepening search

### Informed search
Idea: give the algorithm “hints” about the desirability of different states. Use an evaluation function to rank nodes and select the most promising one for expansion
* Greedy best-first search
* A* search

### Heuristic function
Heuristic function h(n) estimates the cost of reaching goal from node n

Relaxed heuristic functions
* Pattern Database Heuristics 
* Linear Conflict Heuristics
* Gaschnig’s Heuristics

### Future works
* Try with advanced heuristic functions

### Resources
1. [Blog] Problem Solving Techniques part1: https://mhesham.wordpress.com/2010/04/08/problem-solving-techniques-part1/
2. [Blog] Problem Solving Techniques part2: https://mhesham.wordpress.com/tag/depth-limited-search/
3. [Github Repo] Heavily influenced by:
    * C-Collamar's 8-Puzzle-Solver: https://github.com/C-Collamar/8-Puzzle-Solver
    * wolfchimneyrock's 8-Puzzle-Solver: https://github.com/wolfchimneyrock/8-Puzzle-Solver

