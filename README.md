# Puzzle Solver (by using problem solving techniques)

## Project Goal

The goal of this project is to build a generic interactive plugable application for solving puzzles (i.e. 8-puzzle, 8-queen, Sudoku, etc.) using different problem solving techniques (i.e. informed search, uninformed search, etc.).
Here the plugable means, user can independently decide the search strategy along with the custom heuristic functions. If needed, user can choose to implement their own versions for them.

Besides, this application is designed in a way that, it will be a easy going platform for further extension of puzzles/strategy/heuristics.

### Search Strategies
A search strategy is defined by picking the order of node expansion, Strategies are evaluated along the following dimensions:
* Completeness: does it always find a solution if one exists?
* Optimality: does it always find a least-cost solution?
* Time complexity: number of nodes generated
* Space complexity: maximum number of nodes in memory

Time and space complexity are measured in terms of
* b: maximum branching factor of the search tree
* d: depth of the optimal solution
* m: maximum length of any path in the state space (may be infinite)

### Uninformed Search Strategies
Uninformed search strategies use only the information available in the problem definition
* Breadth-first search
* Uniform-cost search
* Depth-first search
* Iterative deepening search

### Informed Search
Idea: give the algorithm “hints” about the desirability of different states. Use an evaluation function to rank nodes and select the most promising one for expansion
* Greedy best-first search
* A* search

### Heuristic Function
Heuristic function h(n) estimates the cost of reaching goal from node n

Relaxed heuristic functions
* Pattern Database Heuristics 
* Linear Conflict Heuristics
* Gaschnig’s Heuristics

## How to Build

```
# go to project directory
$ cd puzzle-solver

# build the project
$ make clean && make
```

## How to Run

General run command:
```
./puzzle -problem {PUZZLE_NAME} -algo {ALGORITHM_NAME} -mode {MODE} -heu {HEURISTIC_METHOD} -initial {INITIAL_STATE_OF_THE_GAME} -goal {GOAL_STATE_OF_THE_GAME} -print_path {PRINT_INITIAL_TO_GOAL}
```

Here is the parameter definition,
1. **-problem:** Specify the puzzle name to solve, for example, "8-puzzle".
2. **-algo:** Specify the search strategy to solve the puzzle, for example, "A*", "bfs", "dfs", etc.
3. **-mode:** Specify the inner methodology for the search strategy, for example, "bi-directional" bfs, "stack-based" dfs, etc.
4. **-heuristic:** Specify the heuristic function you want to use, for example, "hamming", "manhattan", "euclidean", etc. [default: manhattan]
5. **-initial:** Specify the initial board setup for your puzzle
6. **-goal:** Specify the goal state of your puzzle
7. **-print_path:** Flag to indicate printing path if solution exist. Possible options "true"/"false".

## 8-puzzle

### Implementation Domain

Currently I have implemented the following heuristic functions:

| Heuristic Functions | Parameter token for this application |
| --- | --- |
| Hamming Distance | hamming |
| Manhattan Distance | manhattan |
| Euclidean Distance | euclidean |

If you do not specify any particular heuristic function in the program parameter, `manhattan` will be considered as the default one. 

I have used the following algorithms (with the modes) for solving 8-puzzle,

|  | bi-directional | greedy | recursive | stack-based | optimized |
| --- | --- | --- | --- | --- | --- |
| a_star | - | - | - | - | - |
| ida_star | - | - | - | - | - |
| bfs | y | y | - | - | y |
| dfs | - | - | y | y | - |
| dls | y | - | - | - | - |
| ids | y | - | - | - | - |

Please keep in mind that, for the current implementation all the names specified above is actually expected as the parameter name.

### 8-Puzzle Run Commands

For 8-puzzle, here is the list of run commands for different implemented algorithms along with the corresponding mode.

* A*
```
./puzzle -problem 8-puzzle -algo a_star -mode na -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* IDA*
```
./puzzle -problem 8-puzzle -algo ida_star -mode na -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* BFS
```
./puzzle -problem 8-puzzle -algo bfs -mode na -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* Optimized BFS
```
./puzzle -problem 8-puzzle -algo bfs -mode optimized -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* BFS Greedy
```
./puzzle -problem 8-puzzle -algo bfs -mode greedy -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* Bi-directional BFS
```
./puzzle -problem 8-puzzle -algo bfs -mode bi-directiona -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* Recursive DFS
```
./puzzle -problem 8-puzzle -algo dfs -mode recursive -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* Stack Based DFS
```
./puzzle -problem 8-puzzle -algo dfs -mode stack-based -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* DLS
```
./puzzle -problem 8-puzzle -algo dls -mode na -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* Bi-directional DLS
```
./puzzle -problem 8-puzzle -algo dls -mode bi-directional -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* IDS
```
./puzzle -problem 8-puzzle -algo ids -mode na -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

* Bi-directional IDS
```
./puzzle -problem 8-puzzle -algo ids -mode bi-directional -heu manhattan -initial 1,2,3,7,4,5,6,8,0 -goal 1,2,3,8,6,4,7,5,0 -print_path false
```

### Basic Algorithm Description

### Sample Bord Configuration
|  | initial state | goal state |  | initial state | goal state |
| --- | --- | --- | --- | --- | --- |
| input [1] | 1 2 3<br>7 4 5<br>6 8 0 | 1 2 3<br>8 6 4<br>7 5 0 | input [2] | 2 8 1<br>3 4 6<br>7 5 0 | 3 2 1<br>8 0 4<br>7 5 6 |
| input [3] | 1 2 3<br>4 5 6<br>7 8 0 | 1 2 3<br>4 5 6<br>7 8 0 | input [4] | 2 8 1<br>3 4 6<br>7 5 0 | 2 1 6<br>3 8 0<br>7 4 5 |
| input [5] | 4 1 3<br>2 5 6<br>7 8 0 | 1 2 3<br>4 5 6<br>7 8 0 | input [6] | 1 2 3<br>4 5 6<br>7 8 0 | 1 2 3<br>4 8 5<br>7 6 0 |
| input [7] | 8 6 7<br>2 5 4<br>3 0 1 | 1 2 3<br>4 5 6<br>7 8 0 | input [8] | 6 4 7<br>8 5 0<br>3 2 1 | 1 2 3<br>4 5 6<br>7 8 0 |
| input [9] | 2 1 3<br>8 0 4<br>6 7 5 | 1 2 3<br>4 5 6<br>7 8 0 | input [10] | 1 3 4<br>8 6 2<br>7 0 5 | 1 2 3<br>8 0 4<br>7 6 5 |

### Output for the Sample Bord Configuration

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

<table>
  <tr>
    <td>
       <img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/8puzzle_algo_compare_input_1.png" alt="8puzzle_algo_comp_input_1"/>
    </td>
    <td><img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/8puzzle_algo_compare_input_4.png" alt="8puzzle_algo_comp_input_4"/>
    </td>
    <td><img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/8puzzle_algo_compare_input_8.png" alt="8puzzle_algo_comp_input_8"/>
    </td>
  </tr>
  <tr>
    <td align="middle">Figure 1 (a): Input 1</td>
    <td align="middle">Figure 1 (b): Input 4</td>
    <td align="middle">Figure 1 (c): Input 8</td>
  </tr>
  <tr>
    <td colspan="3" align="middle">Figure 1: Comparing performance of different algorithms for solving 8-puzzle</td>
  </tr>
</table>

Here is the list of node generated and expanded by the A* algorithm for different heuristic functions,

| Heuristic\Input | input [1] | input [2] | input [3] | input [4] | input [5] | input [6] | input [7] | input [8] | input [9] | input [10] |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Manhattan Distance | 17 / 9  | 12 / 6 | 1 / 0 | 10 / 5 | 32 / 16 | 8 / 4  | 11927 / 7535    | 13119 / 8296    | X -> 241921 / 181440 | 10 / 5 |
| Hamming Distance   | 40 / 21 | 14 / 7 | 1 / 0 | 10 / 5 | 39 / 21 | 10 / 5 | 186288 / 128467 | 179773 / 122814 | X -> 241921 / 181440 | 12 / 6 |
| Euclidean Distance | 17 / 9  | 12 / 6 | 1 / 0 | 10 / 5 | 32 / 16 | 8 / 4  | 195 / 116       | 121 / 73        | X -> 241921 / 181440 | 10 / 5 |

<table>
  <tr>
    <td>
       <img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/8puzzle_a_star_heuristic_compare_input_1.png" alt="a*_heuristic_comp_input_1"/>
    </td>
    <td><img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/8puzzle_a_star_heuristic_compare_input_7.png" alt="a*_heuristic_comp_input_7"/>
    </td>
    <td><img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/8puzzle_a_star_heuristic_compare_input_8.png" alt="a*_heuristic_comp_input_8"/>
    </td>
  </tr>
  <tr>
    <td align="middle">Figure 2 (a): Input 1</td>
    <td align="middle">Figure 2 (b): Input 7</td>
    <td align="middle">Figure 2 (c): Input 8</td>
  </tr>
  <tr>
    <td colspan="3" align="middle">Figure 2: Comparing performance of different heuristic methods for solving 8-puzzle using A* algorithm</td>
  </tr>
</table>

### Future works
* Try with advanced heuristic functions

### Resources
1. [Blog] Problem Solving Techniques part1: https://mhesham.wordpress.com/2010/04/08/problem-solving-techniques-part1/
2. [Blog] Problem Solving Techniques part2: https://mhesham.wordpress.com/tag/depth-limited-search/
3. [Github Repo] Heavily influenced by:
    * C-Collamar's 8-Puzzle-Solver: https://github.com/C-Collamar/8-Puzzle-Solver
    * wolfchimneyrock's 8-Puzzle-Solver: https://github.com/wolfchimneyrock/8-Puzzle-Solver

