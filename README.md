# Puzzle Solver (by using problem solving techniques)

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

For solving 8-puzzle, I have implemented the algorithms (with the modes) listed bellow.

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
./puzzle -problem {PUZZLE_NAME} -algo {ALGORITHM_NAME} -mode {MODE} -heu {HEURISTIC_METHOD} -initial {INITIAL_STATE_OF_THE_GAME} -goal {GOAL_STATE_OF_THE_GAME} -print_path {PRINT_INITIAL_TO_GOAL}
```
For 8-puzzle, here is the list of run commands for different implemented algorithms along with the corresponding mode.

* stack-based dfs
```
./puzzle -problem 8-puzzle -algo dfs -mode stack-based -heu manhattan -initial 1,2,0,4,5,3,7,8,6 -goal 1,2,3,4,5,6,7,8,0 -print_path false
```

* a-star
```
./puzzle -problem 8-puzzle -algo a_star -mode na -heu manhattan -initial 2,1,3,8,0,4,6,7,5 -goal 1,2,3,4,5,6,7,8,0 -print_path false
```

./puzzle -problem 8-puzzle -algo bfs -mode optimized -heu manhattan -initial 2,8,1,3,4,6,7,5,0 -goal 2,1,6,3,8,0,7,4,5 -print_path false
./puzzle -problem 8-puzzle -algo a_star -mode na -heu hamming -initial 1,2,3,4,5,6,7,0,8 -goal 1,2,3,4,5,6,7,8,0 -print_path false

### Sample bord configuration
|  | initial state | goal state |
| --- | --- | --- |
| input [1] | <p>1 2 3<br>7 4 5<br>6 8 0</p> | <p>1 2 3<br>8 6 4<br>7 5 0</p> |
| input [2] | <p>2 8 1<br>3 4 6<br>7 5 0</p> | <p>3 2 1<br>8 0 4<br>7 5 6</p> |
| input [3] | <p>1 2 3<br>4 5 6<br>7 8 0</p> | <p>1 2 3<br>4 5 6<br>7 8 0</p> |
| input [4] | <p>2 8 1<br>3 4 6<br>7 5 0</p> | <p>2 1 6<br>3 8 0<br>7 4 5</p> |
| input [5] | <p>4 1 3<br>2 5 6<br>7 8 0</p> | <p>1 2 3<br>4 5 6<br>7 8 0</p> |
| input [6] | <p>1 2 3<br>4 5 6<br>7 8 0</p> | <p>1 2 3<br>4 8 5<br>7 6 0</p> |
| input [7] | <p>8 6 7<br>2 5 4<br>3 0 1</p> | <p>1 2 3<br>4 5 6<br>7 8 0</p> |
| input [8] | <p>6 4 7<br>8 5 0<br>3 2 1</p> | <p>1 2 3<br>4 5 6<br>7 8 0</p> |
| input [9] | <p>2 1 3<br>8 0 4<br>6 7 5</p> | <p>1 2 3<br>4 5 6<br>7 8 0</p> |
| input [10] | <p>1 3 4<br>8 6 2<br>7 0 5</p> | <p>1 2 3<br>8 0 4<br>7 6 5</p> |

### Output for the sample bord configuration

Here is the list of node generated and expanded by the algorithms,

| Algorithm\Input | input [1] | input [2] | input [3] | input [4] | input [5] | input [6] | input [7] | input [8] | input [9] | input [10] |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| a_star               | 17 / 9          | 12 / 6        | 1 / 0 | 10 / 5         | 32 / 16            | 8 / 4          | 11927 / 7535    | 13119 / 8296    | X -> 241921 / 181440    | 10 / 5         |
| ida_star             | 19 / 9          | 13 / 6        | 1 / 0 | 11 / 5         | 29 / 13            | 10 / 4         | 8549 / 5336     | 11427 / 7122    | X -> 13822196 / 8491127 | 12 / 5         |
| bfs                  | 328 / 196       | 104 / 63      | 1 / 1 | 71 / 42        | 333 / 203          | 37 / 20        | 181440 / 181440 | 181440 / 181440 | X -> 181440 / 181440    | 69 / 38        |
| bfs [optimized]      | 195 / 113       | 62 / 37       | 1 / 0 | 41 / 24        | 202 / 116          | 19 / 10        | 181439 / 181385 | 181439 / 181399 | X -> 181440 / 181440    | 37 / 22        |
| bfs [greedy]         | 17 / 9          | 12 / 6        | 1 / 0 | 10 / 5         | 20 / 10            | 8 / 4          | 146 / 89        | 213 / 123       | X -> 181440 / 181440    | 10 / 5         |
| bfs [bi-directional] | 59 / 29         | 34 / 19       | 2 / 0 | 20 / 10        | 49 / 24            | 12 / 6         | 16129 / 10240   | 16164 / 10261   | X -> 362878 / 362657    | 24 / 11        |
| dfs [recursive]      | 45902 / 25414   | segfault      | 1 / 0 | 47 / 25        | 3302 / 1825        | 1539 / 849     | segfault        | segfault        | segfault                | 58013 / 32132  |
| dfs [stack-based]    | 172532 / 139521 | 44928 / 25911 | 0 / 0 | 132509 / 89866 | 106652 / 67853     | 53 / 30        | 111292 / 71403  | 112424 / 72473  | X -> 181439 / 181440    | 98579 / 61635  |
| dls                  | 89990 / 54204   | 89991 / 54206 | 1 / 0 | 121282 / 73158 | X -> 89991 / 54205 | 110642 / 66666 | 104943 / 58901  | 103680 / 58336  | X -> 111711 / 67385     | 104943 / 58903 |
| dls [bi-directional] | 2515 / 1517     | 2782 / 1677   | 1 / 0 | 4665 / 2802    | 6809 / 4072        | 2801 / 1687    | 16254 / 9094    | 7751 / 4319     | X -> 29119 / 17439      | 1303 / 727     |
| ids                  | 720 / 423       | 662 / 390     | 1 / 0 | 47 / 25        | segfault           | 669 / 394      | segfault        | 92439 / 51938   | segfault                | 52477 / 29331  |
| ids [bi-directional] | 2515 / 1517     | 2782 / 1677   | 1 / 0 | 4665 / 2802    | 6809 / 4072        | 2801 / 1687    | 16253 / 9094    | 7750 / 4319     | segfault                | 1303 / 727     |

Here is the list of node generated and expanded by the A* algorithm for different heuristic functions,

| Heuristic\Input | input [1] | input [2] | input [3] | input [4] | input [5] | input [6] | input [7] | input [8] | input [9] | input [10] |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Manhattan Distance | 17 / 9  | 12 / 6 | 1 / 0 | 10 / 5 | 32 / 16 | 8 / 4  | 11927 / 7535    | 13119 / 8296    | X -> 241921 / 181440 | 10 / 5 |
| Hamming Distance   | 40 / 21 | 14 / 7 | 1 / 0 | 10 / 5 | 39 / 21 | 10 / 5 | 186288 / 128467 | 179773 / 122814 | X -> 241921 / 181440 | 12 / 6 |
| Euclidean Distance | 17 / 9  | 12 / 6 | 1 / 0 | 10 / 5 | 32 / 16 | 8 / 4  | 195 / 116       | 121 / 73        | X -> 241921 / 181440 | 10 / 5 |

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

