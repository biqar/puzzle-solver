# Game Solver (by using problem solving techniques)

### Project goal

The goal of this project is to build a generic interactive plugable application for solving puzzles (i.e. 8-puzzle, 8-queen, Sudoku, etc.) using different problem solving techniques (i.e. informed search, uninformed search, etc.).
Here the plugable means, user can independently decide the search strategy along with the custom heuristic functions. If needed, user can choose to implement their own versions for them.

Besides, this application is designed in a way that, it will be a easy going platform for further extension of puzzles/strategy/heuristics.

### Restriction to use

Currently I have implemented the following heuristic functions:

| Heuristic Functions | Parameter token for this application |
| --- | --- |
| Hamming Distance | hamming |
| Manhattan Distance | manhattan |
| Euclidean Distance | euclidean |

If you do not specify any particular heuristic function in the program parameter, `manhattan` will be considered as the default one. 

For solving 8-puzzle game, I have implemented the algorithms (with the modes) listed bellow.

|  | bi-directional | greedy | recursive | stack-based | optimized |
| --- | --- | --- | --- | --- | --- |
| a_star | - | - | - | - | - |
| ida_star | - | - | - | - | - |
| bfs | y | y | - | - | y |
| dfs | - | - | y | y | - |
| dls | y | - | - | - | - |
| ids | y | - | - | - | - |

### How to run
General run command:

```
./puzzle -problem {PUZZLE_NAME} -algo {ALGORITHM_NAME} -mode {MODE} -heu {HEURISTIC_METHOD} -initial {INITIAL_STATE_OF_THE_GAME} -goal {GOAL_STATE_OF_THE_GAME} -print_path {YES/NO}
```
For 8-puzzle game, here is the list of run commands for different implemented algorithms along with the corresponding mode.

* stack-based dfs
```
./puzzle -problem 8-puzzle -algo dfs -mode stack-based -heu manhattan -initial 1,2,0,4,5,3,7,8,6 -goal 1,2,3,4,5,6,7,8,0 -print_path false
```

* a-star
```
./puzzle -problem 8-puzzle -algo a_star -mode na -heu manhattan -initial 2,1,3,8,0,4,6,7,5 -goal 1,2,3,4,5,6,7,8,0 -print_path false
```

./puzzle -problem 8-puzzle -algo a_star -mode na -heu manhattan -initial 1,2,3,4,5,6,7,8,0 -goal 1,2,3,4,5,6,7,8,0 -print_path false
./puzzle -problem 8-puzzle -algo a_star -mode na -heu hamming -initial 1,2,3,4,5,6,7,0,8 -goal 1,2,3,4,5,6,7,8,0 -print_path false

### Sample bord configuration
|  | initial state | goal state |
| --- | --- | --- |
| input [1] | 1,2,3,7,4,5,6,8,0 | 1,2,3,8,6,4,7,5,0 |
| input [2] | 2,8,1,3,4,6,7,5,0 | 3,2,1,8,0,4,7,5,6 |
| input [3] | 1,2,3,4,5,6,7,8,0 | 1,2,3,4,5,6,7,8,0 |
| input [4] | 2,8,1,3,4,6,7,5,0 | 2,1,6,3,8,0,7,4,5 |
| input [5] | 4,1,3,2,5,6,7,8,0 | 1,2,3,4,5,6,7,8,0 |
| input [6] | 1,2,3,4,5,6,7,8,0 | 1,2,3,4,8,5,7,6,0 |
| input [7] | 8,6,7,2,5,4,3,0,1 | 1,2,3,4,5,6,7,8,0 |
| input [8] | 6,4,7,8,5,0,3,2,1 | 1,2,3,4,5,6,7,8,0 |
| input [9] | 2,1,3,8,0,4,6,7,5 | 1,2,3,4,5,6,7,8,0 |
| input [10] | 1,2,3,4,5,6,7,8,0 | 1,2,3,4,5,6,7,8,0 |

### Output for the sample bord configuration

Here is the list of node generated and expanded by the algorithms,

| Algorithm\Input | input [1] | input [2] | input [3] | input [4] | input [5] | input [6] | input [7] | input [8] | input [9] | input [10] |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| a_star | - | - | - | - | - | - | - | - | - | - |
| ida_star | - | - | - | - | - | - | - | - | - | - |
| bfs | - | - | - | - | - | - | - | - | - | - |
| bfs [optimized] | - | - | - | - | - | - | - | - | - | - |
| bfs [greedy] | - | - | - | - | - | - | - | - | - | - |
| bfs [bi-directional] | - | - | - | - | - | - | - | - | - | - |
| dfs [recursive] | - | - | - | - | - | - | - | - | - | - |
| dfs [stack-based] | - | - | - | - | - | - | - | - | - | - |
| dls | - | - | - | - | - | - | - | - | - | - |
| dls [bi-directional] | - | - | - | - | - | - | - | - | - | - |
| ids | - | - | - | - | - | - | - | - | - | - |
| ids [bi-directional] | - | - | - | - | - | - | - | - | - | - |

Here is the list of node generated and expanded by the A* algorithm for different heuristic functions,

| Heuristic\Input | input [1] | input [2] | input [3] | input [4] | input [5] | input [6] | input [7] | input [8] | input [9] | input [10] |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Manhattan Distance | - | - | - | - | - | - | - | - | - | - |
| Hamming Distance | - | - | - | - | - | - | - | - | - | - |
| Euclidean Distance | - | - | - | - | - | - | - | - | - | - |

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

